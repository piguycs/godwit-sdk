#include "engine/engine.h"

#include <raylib.h>

#include <memory>

#include "engine/camera.h"
#include "engine/renderables.h"

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

Camera3D getRlCamera(const engine::Camera& mainCamera) {
    Camera3D camera;
    camera.position = {mainCamera.posX, mainCamera.posY, mainCamera.posZ};
    camera.target = {mainCamera.targetX, mainCamera.targetY, mainCamera.targetZ};
    camera.up = {mainCamera.upX, mainCamera.upY, mainCamera.upZ};
    camera.fovy = mainCamera.fovy;
    camera.projection = CAMERA_PERSPECTIVE;

    return camera;
}

namespace engine {

Engine Engine::init(bool defaultSystems) {
    Engine engine;

    if (defaultSystems) {
        // 2D and 3D render contexts (queues)
        // both are functionally the same, but having them aliased like this allows the
        // function signatures of our systems to indicate what the system is doing
        engine.registerResource<RenderCtx2D>();
        engine.registerResource<RenderCtx3D>();

        // TODO: make this configurable via some other resource
        engine.registerResource<Camera>(
            0.0f, 10.0f, 10.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            45.0f
        );
    }

    return engine;
}

void Engine::start() {
    WindowHandle _windowHandle(800, 450, "Godwit SDK (ECS) game");
    SetTargetFPS(60);

    std::vector<std::shared_ptr<engine::IRenderable2D>> deferred2D;

    while (!WindowShouldClose()) {
        resourceManager.runSystemsOnce();

        DrawingHandle _drawingHandle;
        auto& ctx2d = resourceManager.getResource<engine::RenderCtx2D>();

        // we render all the immediate 2D renderables, but deferred ones are put to the end
        for (auto& renderable : ctx2d.queue) {
            if (renderable->shouldDefer()) {
                deferred2D.push_back(renderable);
            } else {
                renderable->renderFunction();
            }
        }

        auto& mainCamera = resourceManager.getResource<engine::Camera>();
        auto& ctx3d = resourceManager.getResource<engine::RenderCtx3D>();

        {
            DrawHandle3D _drawHandle3D(getRlCamera(mainCamera));

            // all the 3D renderables are rendered over here
            for (auto& renderable : ctx3d.queue) renderable->renderFunction();

            ctx3d.queue.clear();
        }

        // render all the deferred renderables
        for (auto& renderable : deferred2D) renderable->renderFunction();

        deferred2D.clear();
        ctx2d.queue.clear();
    }
}

}  // namespace engine
