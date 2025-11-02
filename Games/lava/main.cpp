#include <godwit.hpp>
#include <godwit/drawmode.hpp>
#include <iostream>
#include <random>
#include <raylib.h>
#include "griditer.hpp"
#include "state.hpp"

const int GRID_SIZE = 50;
const float CAMERA_RADIUS = GRID_SIZE * 1.5f;
const float ROTATION_SPEED = 0.005f;

GameState on_start() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "GODWIT VERSION: " << GODWIT_SDK_VERSION << std::endl;

    // setting up the camera to some good defaults

    std::mt19937 rng(42); // fixed seed
    std::uniform_real_distribution<float> dist(0.f, 1.f);
    constexpr float alive_percent = 0.05f;

    auto grid = CellGrid::init(GRID_SIZE);

    for (auto [x,y,z] : XYZRange(GRID_SIZE)) {
        if (dist(rng) < alive_percent) {
            grid.set_life_at(x, y, z, Alive);
        }
    }

    SimRule rule; // we roll with the default values here
    lava::Camera camera(GRID_SIZE, CAMERA_RADIUS);

    return GameState{0.f, grid, camera, rule};
}

void draw(const Cell& cell, std::uint32_t x, std::uint32_t y, std::uint32_t z) {
    if (cell.life == Alive) {
        DrawCube({(float)x, (float)y, (float)z}, 1.f, 1.f, 1.f, BLUE);
    } else if (cell.life == Decaying) {
        DrawCube({(float)x, (float)y, (float)z}, 1.f, 1.f, 1.f, ORANGE);
    }
}

void on_update(GameState& state) {
    state.camera.rotate(ROTATION_SPEED, GRID_SIZE);
    
    BeginDrawing();

    ClearBackground(BLACK);

    {
        DrawHandle3D handle(state.camera.rlCam3d());
        for (auto [x,y,z] : XYZRange(GRID_SIZE)) {
            auto cell = state.grid.at(x,y,z);
            draw(cell, x, y, z);
        }
    }

    // this might be more inefficient, as I am looping twice with this
    // it might be more efficient to add a draw callback, and then move this call up in the draw loop
    state.grid.step(GRID_SIZE, state.rule);

    DrawFPS(10,10);

    EndDrawing();
}

void cleanup() {
    std::cout << "Goodbye!" << std::endl;
}

int main() {
    std::string level_name = "stage";

    LevelConfig config;
    
    auto level_opt = Level<GameState>::init(level_name, on_start, on_update, cleanup, config);

    if (auto level = level_opt) {
        level->start_loop_blocking();
    } else {
        std::cerr << "Unable to initialise level " << level_name << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

WIN32_GLUE(main)
