#pragma once

#include <engine/engine.h>
#include <engine/camera.h>
#include "grid.hpp"

struct Config {
    bool renderFps = true;
    engine::RGB backgroundColour = {0,0,0};
    engine::RGB aliveColour = {137, 252, 131};
    engine::RGB decayingColour = {252, 145, 131};
};

void renderFps(engine::RenderCtx2D& ctx, const Config& cfg);
void renderBackground(engine::RenderCtx2D& ctx, const Config& cfg);
void stepGridSystem(Grid& grid, const SimRules& rules);
void drawGrid(engine::RenderCtx3D& ctx, const Grid&, const Config& cfg);
void rotateCamera(engine::Camera& camera);
