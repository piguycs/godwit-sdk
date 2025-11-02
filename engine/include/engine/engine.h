#pragma once

#include "engine/resource.h"
#include <raylib.h>

namespace engine {

class Engine {
    
public:
    Engine() = default;
    ~Engine() = default;

    void start() {
    }

    template<typename T, typename... Args>
    void registerResource(Args&&... args) {
        resourceManager.registerResource<T>(std::forward<Args>(args)...);
    }

    template<typename Func>
    void addSystem(Func&& func) {
        resourceManager.addSystem(std::forward<Func>(func));
    }

private:
    ResourceManager resourceManager;
};

}
