#include "engine/renderables.h"
#include <raylib.h>

namespace engine {


bool FpsRender::shouldDefer() {
    return true;
}

void FpsRender::renderFunction() {
    DrawFPS(x, y);
}

void ClearBackgroundRender::renderFunction() {
    // OLD COLOUR: Color{130, 130, 252, 255}
    Color rlColor{colour.r, colour.g, colour.b, 255};
    ClearBackground(rlColor);
}

void CubeRender::renderFunction() {
    Vector3 pos{position.x, position.y, position.z};
    Color rlColor{colour.r, colour.g, colour.b, 255};
    DrawCube(pos, scale.width, scale.height, scale.depth, rlColor);
}

}
