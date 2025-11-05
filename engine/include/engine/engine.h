#pragma once

#include "engine/resource.h"
#include "engine/render.h"
#include "engine/camera.h"

const int CAMERA_MAIN = 0;

namespace engine {

class Engine {
    ResourceManager resourceManager;
    Engine() = default;
    
public:
    static Engine init(bool defaultSystems = true) {
        Engine engine;

        if (defaultSystems) {
            // 2D and 3D render contexts (queues)
            // both are functionally the same, but having them aliased like this allows the
            // function signatures of our systems to indicate what the system is doing
            engine.registerResource<RenderCtx2D>();
            engine.registerResource<RenderCtx3D>();

            // TODO: make this configurable via some other resource
            engine.registerResource<Camera<CAMERA_MAIN>>(
                0.0f, 10.0f, 10.0f,
                0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                45.0f
            );
        }

        return engine;
    }

    void start();

    template<typename T, typename... Args>
    void registerResource(Args&&... args) {
        resourceManager.registerResource<T>(std::forward<Args>(args)...);
    }

    template<typename Func>
    void addSystem(Func&& func) {
        resourceManager.addSystem(std::forward<Func>(func));
    }
};

}
