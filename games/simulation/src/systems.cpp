#include "systems.hpp"
#include "engine/renderables.h"
#include "griditer.hpp"

void renderFps(engine::RenderCtx2D& ctx, const Config& cfg) {
    if (cfg.renderFps) ctx.add<engine::FpsRender>(10, 10);
}

void renderBackground(engine::RenderCtx2D& ctx) {
    ctx.add<engine::ClearBackgroundRender>();
}

void stepGridSystem(Grid& grid, const SimRules& rules) {
    grid.step(rules);
}

void drawGrid(engine::RenderCtx3D& ctx, const Grid& grid) {
    for (auto [x,y,z] : XYZRange(GRID_SIZE)) {

        const Cell& cell = grid.at(x, y, z);
        
        switch (cell.life) {
            case Dead: break; // we do nothing for dead cells

            // set the colour which is important for both Alive and Decaying
            engine::RGB colour;

            case Alive:
                colour = {137, 252, 131};
            // intentional fallthrough
            case Decaying:
                colour = {252, 145, 131};

                engine::Position3D position(x, y, z);
                engine::Scale scale(1, 1, 1);

                ctx.add<engine::CubeRender>(scale, position, colour);
                break;
        }
    }
    
}

void rotateCamera(engine::Camera& camera) {
    camera.posX += 0.1f;
    // camera.posY += 0.1f;
    camera.posZ += 0.1f;
}

