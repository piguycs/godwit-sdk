#include "engine/engine.h"
#include "raylib.h"

namespace engine {

void Engine::start() {
    InitWindow(800, 450, "Godwit SDK (ECS) game");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        resourceManager.runOtherSystemsOnce();

        BeginDrawing();
        EndDrawing();
    }

    CloseWindow();
}

}
