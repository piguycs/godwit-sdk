#include "engine/engine.h"
#include "engine/raylib.h"
#include "grid.hpp"
#include "rules.hpp"

void renderFps(raylib::RenderCtx2D& ctx) { ctx.DrawFPS(10, 10); }

void stepGridSystem(Grid& grid, const SimRules& rules) {
    grid.step(rules);
}

void drawGrid(const Grid&) {
    // TODO
}

int main() {
    engine::Engine engine;

    engine.registerResource<Grid>();
    engine.registerResource<SimRules>();

    engine.addSystem(renderFps);
    engine.addSystem(drawGrid);

    engine.start();
}
