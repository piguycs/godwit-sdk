#include "engine/engine.h"
#include "grid.hpp"
#include "rules.hpp"

void renderFps() { raylib::DrawFPS(10, 10); }

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
