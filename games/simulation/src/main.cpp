#include <engine/engine.h>
#include <engine/camera.h>
#include "systems.hpp"

int main() {
    engine::Engine engine = engine::Engine::init();

    engine.registerResource<Grid>();
    engine.registerResource<SimRules>();
    engine.registerResource<Config>();
    engine.registerResource<CameraMeta>();

    engine.addSystem(rotateCamera);
    engine.addSystem(stepGridSystem);

    engine.addSystem(renderBackground);
    engine.addSystem(renderFps);

    engine.addSystem(drawGrid);


    engine.start();
}
