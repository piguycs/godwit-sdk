#include <iostream>
#include <godwit/godwit.hpp>
#include <raylib.h>
#include "main.h"

int main() {
    std::string level_name = "Game1";
    auto level_opt = Level::init(level_name, on_start, on_update, cleanup, {});

    if (auto level = level_opt) {
        level->start_loop_blocking();
    } else {
        std::cerr << "Unable to initialise level " << level_name << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void on_start() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "GODWIT VERSION: " << GODWIT_SDK_VERSION << std::endl;
}

void on_update() {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    EndDrawing();
}

void cleanup() {
    std::cout << "Goodbye!" << std::endl;
}
