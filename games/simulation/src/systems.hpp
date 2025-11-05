#pragma once

#include <engine/camera.h>
#include <engine/engine.h>

#include "grid.hpp"

// some other colour that I was trying
// engine::RGB decayingColour = {137, 252, 131};

struct Config {
    bool renderFps = true;

    engine::RGB backgroundColour = {0, 0, 0};
    engine::RGB aliveColour = {0, 121, 241};
    engine::RGB decayingColour = {255, 161, 0};
    // colour for the bounding box surrounding the simulation
    engine::RGB boundingBoxColour = {2, 237, 18};

    float rotationSpeed = 0.005f;
};

// some extra data related to the camera which we use for our game-specific logic
struct CameraMeta {
    float angle;
    float radius = GRID_SIZE * 1.5f;
};

void renderFps(engine::RenderCtx2D& ctx, const Config& cfg);
void renderBackground(engine::RenderCtx2D& ctx, const Config& cfg);
void stepGridSystem(Grid& grid, const SimRules& rules);
void drawGrid(engine::RenderCtx3D& ctx, const Grid&, const Config& cfg);
void rotateCamera(engine::Camera& camera, CameraMeta& camMeta, const Config& cfg);
