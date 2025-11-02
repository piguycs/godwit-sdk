#pragma once

// TODO: change naming convention from Rust's to C++'s

#include <optional>
#include <string>
#include <raylib.h>
#include <functional>

extern const char* GODWIT_SDK_VERSION;

struct LevelConfig {
    int window_height = 450;
    int window_width = 800;
    int preferred_fps = 60;
    std::string title = "3D Cellular Automata Simulation";
};

/// A level is the main state driving the game engine. A game can have a single
/// level, or multiple levels. Each level has it's own hooks for startup, update
/// and cleanup. A Level can switch to another level, where it transfers the
/// underlying window and engine config, but does not transfer the state. This
/// is the preferred way of switching between level (and it is TODO)
template <typename TLevelState>
class Level {

public: /* static functions */
    /// Initialise a level with this function. The Constructor for this class is
    /// private.
    static std::optional<Level> init(
            std::string& name,
            std::function<TLevelState()> on_start,
            std::function<void(TLevelState&)> on_update,
            std::function<void()> cleanup,
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

public: /* public methods */
    void start_loop_blocking() {
        TLevelState state = this->m_onStart();

        while (!WindowShouldClose()) {
            this->m_onUpdate(state);
        }

        this->m_cleanup();
    }

public: /* public destructor */
    ~Level() = default;

private: /* private attributes & callbacks */
    LevelConfig m_levelConfig;
    std::string m_name;
    // callbacks for some of the more basic "events".
    std::function<TLevelState()> m_onStart;
    std::function<void(TLevelState&)> m_onUpdate;
    std::function<void()> m_cleanup;

private: /* private constructor */
    Level(
        std::string name,
        std::function<TLevelState()> on_start,
        std::function<void(TLevelState&)> on_update,
        std::function<void()> cleanup,
        LevelConfig level_config
    ) : m_levelConfig(level_config), m_name(name), m_onStart(on_start),
        m_onUpdate(on_update), m_cleanup(cleanup) {}
    };


// --- special glue for making this game work with Windows' archiac "subsystem" model
#ifdef _WIN32
#include <windows.h>
#include <main.h>
#define WIN32_GLUE(main) \
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) { \
        (void)hInstance; \
        (void)hPrevInstance; \
        (void)lpCmdLine; \
        (void)nCmdShow; \
        return main(); \
    }
#else
#define WIN32_GLUE(main) \
    // --- we do nothing here ---
#endif
