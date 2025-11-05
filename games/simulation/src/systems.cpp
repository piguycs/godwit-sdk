#include "systems.hpp"

#include <cmath>

#include "engine/renderables.h"
#include "griditer.hpp"

void renderFps(engine::RenderCtx2D& ctx, const Config& cfg) {
    if (cfg.renderFps) ctx.add<engine::FpsRender>(10, 10);
}

void renderBackground(engine::RenderCtx2D& ctx, const Config& cfg) {
    ctx.add<engine::ClearBackgroundRender>(cfg.backgroundColour);
}

void stepGridSystem(Grid& grid, const SimRules& rules) { grid.step(rules); }

void drawGrid(engine::RenderCtx3D& ctx, const Grid& grid, const Config& cfg) {
    // Draw the bounding box for the entire grid
    engine::Position3D boundingPos(GRID_SIZE / 2.0f, GRID_SIZE / 2.0f, GRID_SIZE / 2.0f);
    engine::Scale boundingScale(GRID_SIZE, GRID_SIZE, GRID_SIZE);
    ctx.add<engine::CubeWiresRender>(boundingScale, boundingPos, cfg.boundingBoxColour);

    for (auto [x, y, z] : XYZRange(GRID_SIZE)) {
        const Cell& cell = grid.at(x, y, z);

        // set the colour which is important for both Alive and Decaying
        engine::RGB colour;

        switch (cell.life) {
            case Dead:
                continue;  // we do nothing for dead cells

            case Alive:
                colour = cfg.aliveColour;
                break;

            case Decaying:
                colour = cfg.decayingColour;
                break;
        }

        engine::Position3D position(x, y, z);
        engine::Scale scale(1, 1, 1);

        ctx.add<engine::CubeRender>(scale, position, colour);
    }
}

void rotateCamera(engine::Camera& camera, CameraMeta& camMeta, const Config& cfg) {
    camMeta.angle += cfg.rotationSpeed;

    // Center of the grid
    float centerX = GRID_SIZE / 2.0f;
    float centerY = GRID_SIZE / 2.0f;
    float centerZ = GRID_SIZE / 2.0f;

    // Position camera in orbit around the center
    camera.posX = centerX + camMeta.radius * std::cos(camMeta.angle);
    camera.posY = centerY + GRID_SIZE / 1.0f;  // Elevated view
    camera.posZ = centerZ + camMeta.radius * std::sin(camMeta.angle);

    // Make the camera look at the center of the grid
    camera.targetX = centerX;
    camera.targetY = centerY;
    camera.targetZ = centerZ;
}
