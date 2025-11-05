#pragma once

#include "engine/resource.h"
#include "engine/render.h"

const int CAMERA_MAIN = 0;

namespace engine {

class Engine {
    ResourceManager resourceManager;
    Engine() = default;
    
public:
    static Engine init(bool defaultSystems = true);
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
