#include "systems.hpp"

void renderFps(engine::RenderCtx2D& ctx, const Config& cfg) {
    if (cfg.renderFps) ctx.add<engine::FpsRender>(10, 10);
}

void renderBackground(engine::RenderCtx2D& ctx) {
    ctx.add<engine::ClearBackgroundRender>();
}

void stepGridSystem(Grid& grid, const SimRules& rules) {
    grid.step(rules);
}

void drawGrid(engine::RenderCtx3D& ctx, const Grid&) {
    ctx.add<engine::CubeRender>(1, 1, 1, 0, 0, 0);
}

void rotateCamera(engine::Camera& camera) {
    camera.posX += 0.1f;
    camera.posY += 0.1f;
    camera.posZ += 0.1f;
}

