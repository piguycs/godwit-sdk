#include "engine/renderables.h"
#include <raylib.h>

namespace engine {

void FpsRender::renderFunction() {
    DrawFPS(x, y);
}

void ClearBackgroundRender::renderFunction() {
    ClearBackground(RAYWHITE);
}

void CubeRender::renderFunction() {
    DrawCube(Vector3{ 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f, RED);
}

}
