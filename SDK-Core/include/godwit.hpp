#pragma once

// TODO: change naming convention from Rust's to C++'s

#include <optional>
#include <string>
#include "godwit/types.hpp"

extern const char* GODWIT_SDK_VERSION;

struct LevelConfig {
    int window_height = 450;
    int window_width = 800;
    int preferred_fps = 60;
    std::string title = "Godwit SDK game";
};

/// A level is the main state driving the game engine. A game can have a single
/// level, or multiple levels. Each level has it's own hooks for startup, update
/// and cleanup. A Level can switch to another level, where it transfers the
/// underlying window and engine config, but does not transfer the state. This
/// is the preferred way of switching between level (and it is TODO)
class Level {

public: /* static functions */
    /// Initialise a level with this function. The Constructor for this class is
    /// private.
    static std::optional<Level> init(
        std::string& name,
        LevelCB on_start,
        LevelCB on_update,
        LevelCB cleanup,
        LevelConfig level_config
    );

public: /* public methods */
    void start_loop_blocking();

public: /* public destructor */
    ~Level() = default;

private: /* private attributes & callbacks */
    LevelConfig m_level_config;
    std::string m_name;
    // callbacks for some of the more basic "events".
    LevelCB m_on_start;
    LevelCB m_on_update;
    LevelCB m_cleanup;

private: /* private constructor */
    Level(
        std::string name,
        LevelCB on_start,
        LevelCB on_update,
        LevelCB cleanup,
        LevelConfig level_config
    );
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
