#include "engine/engine.h"
#include "raylib.h"

// easy handle so that we use RAII for the begin/end drawing
// should also help if any of the systems throw an exception? (would need to test)
struct DrawingHandle {
    DrawingHandle() { BeginDrawing(); }
    ~DrawingHandle() { EndDrawing(); }
};

struct DrawHandle3D {
    DrawHandle3D(Camera3D camera) { BeginMode3D(camera); }
    ~DrawHandle3D() { EndMode3D(); }
};

struct WindowHandle {
    WindowHandle(int width, int height, std::string title) {
        InitWindow(width, height, title.c_str());
    }
    ~WindowHandle() { CloseWindow(); }
};

namespace engine {

void Engine::start() {
    WindowHandle _windowHandle(800, 450, "Godwit SDK (ECS) game");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        resourceManager.runSystemsOnce();

        // these scopes can easily drop the drawing handles with RAII
        {
            DrawingHandle _drawingHandle;
            auto ctx2d = resourceManager.getResource<engine::RenderCtx2D>();
            for (auto& renderable : ctx2d.queue) {
                renderable->renderFunction();
            }
            ctx2d.queue.clear();


            {
                auto mainCamera = resourceManager.getResource<engine::Camera<CAMERA_MAIN>>();
                auto ctx3d = resourceManager.getResource<engine::RenderCtx3D>();

                Camera3D camera; 
                camera.position = { mainCamera.posX, mainCamera.posY, mainCamera.posZ };
                camera.target = { mainCamera.targetX, mainCamera.targetY, mainCamera.targetZ };
                camera.up = { mainCamera.upX, mainCamera.upY, mainCamera.upZ };
                camera.fovy = mainCamera.fovy;
                camera.projection = CAMERA_PERSPECTIVE;

                DrawHandle3D _drawHandle3D(camera);
                for (auto& renderable : ctx3d.queue) {
                    renderable->renderFunction();
                }
            }
        }
    }
}

}
