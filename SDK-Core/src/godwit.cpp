#include <raylib.h>
#include "godwit.hpp"

const char* GODWIT_SDK_VERSION = "2025_05_001";

std::optional<Level> Level::init(
        std::string& name,
        LevelCB on_start,
        LevelCB on_update,
        LevelCB cleanup,
        LevelConfig level_config
) {
    if (name.length() <= 0) return std::nullopt;
    if (on_start == nullptr) return std::nullopt;
    if (on_update == nullptr) return std::nullopt;
    if (cleanup == nullptr) return std::nullopt;

    InitWindow(
        level_config.window_width,
        level_config.window_height,
        level_config.title.c_str()
    );
    SetTargetFPS(level_config.preferred_fps);

    Level level(name, on_start, on_update, cleanup, level_config);
    return level;
}

void Level::start_loop_blocking() {
    this->m_on_start();

    while (!WindowShouldClose()) {
        this->m_on_update();
    }

    this->m_cleanup();
}

/// PRIVTE CONSTRUCTOR FOR LEVEL
Level::Level(
    std::string name,
    LevelCB on_start,
    LevelCB on_update,
    LevelCB cleanup,
    LevelConfig level_config
) : m_level_config(level_config), m_name(name), m_on_start(on_start),
    m_on_update(on_update), m_cleanup(cleanup) {}
