#include "engine/engine.h"
#include "grid.hpp"
#include "rules.hpp"

struct Config {
    bool renderFps = true;
};

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

void rotateCamera(engine::Camera<CAMERA_MAIN>& camera) {
    camera.posX += 0.1f;
    camera.posY += 0.1f;
    camera.posZ += 0.1f;
}

int main() {
    engine::Engine engine = engine::Engine::init();

    engine.registerResource<Grid>();
    engine.registerResource<SimRules>();
    engine.registerResource<Config>();

    engine.addSystem(renderBackground);
    engine.addSystem(renderFps);

    engine.addSystem(drawGrid);
    engine.addSystem(rotateCamera);


    engine.start();
}
