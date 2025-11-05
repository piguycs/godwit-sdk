#pragma once

#include <engine/engine.h>
#include <engine/camera.h>
#include "grid.hpp"

struct Config {
    bool renderFps = true;
};

void renderFps(engine::RenderCtx2D& ctx, const Config& cfg);
void renderBackground(engine::RenderCtx2D& ctx);
void stepGridSystem(Grid& grid, const SimRules& rules);
void drawGrid(engine::RenderCtx3D& ctx, const Grid&);
void rotateCamera(engine::Camera& camera);
