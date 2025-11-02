#include <godwit.hpp>
#include <iostream>
#include <random>
#include <raylib.h>
#include "griditer.hpp"
#include "cells.hpp"

const int HEIGHT = 50;
const int WIDTH = 50;
const int DEPTH = 50;
const float ROTATION_SPEED = 0.005f;

Camera3D camera;
float cam_angle = 0.f;

CellGrid on_start() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "GODWIT VERSION: " << GODWIT_SDK_VERSION << std::endl;

    camera.position = {WIDTH*1.5f, HEIGHT*0.5f, DEPTH*1.5f};
    camera.target = {WIDTH/2.f, HEIGHT/2.f, DEPTH/2.f};
    camera.up = {0,1,0};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    std::mt19937 rng(42); // fixed seed
    std::uniform_real_distribution<float> dist(0.f, 1.f);
    constexpr float alive_percent = 0.017f;

    auto grid = CellGrid::init(WIDTH, HEIGHT, DEPTH);

    for (auto [x,y,z] : XYZRange(WIDTH, HEIGHT, DEPTH)) {
        if (dist(rng) < alive_percent) {
            grid.set_alive_at(x, y, z, true);
        }
    }
    
    return grid;
}

void draw(const Cell& cell, std::uint32_t x, std::uint32_t y, std::uint32_t z) {
    if (cell.alive) {
        DrawCube({(float)x, (float)y, (float)z}, 1.f, 1.f, 1.f, BLUE);
    }
}

void on_update(CellGrid& grid) {
    struct Update {
        std::uint32_t x, y, z;
        bool alive;
    };
    std::vector<Update> update_queue;
    update_queue.reserve(WIDTH * HEIGHT * DEPTH);

    cam_angle += ROTATION_SPEED; // rotation speed
    float radius = WIDTH * 1.5f;
    camera.position.x = grid.width/2.f + radius * cos(cam_angle);
    camera.position.z = grid.depth/2.f + radius * sin(cam_angle);
    camera.position.y = HEIGHT; // sideways/above view
    
    BeginDrawing();

    ClearBackground(BLACK);

    BeginMode3D(camera);

    for (auto [x,y,z] : XYZRange(WIDTH, HEIGHT, DEPTH)) {
        auto cell = grid.at(x,y,z);

        // draw the cell before modifying anything
        draw(cell, x, y, z);

        auto neighbours = grid.count_alive_neighbours(x, y, z);

        // 4/4/5/M
        if (cell.alive && neighbours == 50) {
            // it stays alive
        } else if (!cell.alive && neighbours == 4) {
            // it becomes alive
            update_queue.push_back({x,y,z,true});
            // grid.set_alive_at(x, y, z, true);
        } else {
            // TODO: handle the state parameter
            update_queue.push_back({x,y,z,false});
            // grid.set_alive_at(x, y, z, false);
        }
    }

    EndMode3D();

    for (auto update : update_queue) {
        grid.set_alive_at(update.x, update.y, update.z, update.alive);
    }

    DrawFPS(10,10);

    EndDrawing();
}

void cleanup() {
    std::cout << "Goodbye!" << std::endl;
}

int main() {
    std::string level_name = "stage";

    LevelConfig config;
    
    auto level_opt = Level<CellGrid>::init(level_name, on_start, on_update, cleanup, config);

    if (auto level = level_opt) {
        level->start_loop_blocking();
    } else {
        std::cerr << "Unable to initialise level " << level_name << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

WIN32_GLUE(main)
