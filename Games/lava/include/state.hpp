#pragma once

#include "cells.hpp"
#include "simrule.hpp"
#include "camera.hpp"

struct GameState {
    float cam_angle;
    CellGrid grid;

    lava::Camera camera;

    SimRule rule;
};
