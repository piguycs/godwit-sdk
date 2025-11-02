#pragma once

#include "engine/resource.h"

namespace raylib {
#include <raylib.h>
}


namespace engine {

class Engine {
    
public:
    Engine() = default;
    ~Engine() = default;

    void start() {
        raylib::InitWindow(800, 450, "Godwit SDK (ECS) game");
        raylib::SetTargetFPS(60);

        while (!raylib::WindowShouldClose()) {
            raylib::BeginDrawing();
            raylib::ClearBackground(raylib::RAYWHITE);
            resourceManager.runAllSystemsOnce();
            raylib::EndDrawing();
        }

        raylib::CloseWindow();
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
