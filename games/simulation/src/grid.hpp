#pragma once

#include "src/rules.hpp"
#include <optional>
#include <tl/expected.hpp>

const int GRID_SIZE = 50;
const int GRID_SIZE_3D = GRID_SIZE * GRID_SIZE * GRID_SIZE;

enum LifeState {
    Dead,
    Alive,
    Decaying,
};

struct Cell {
    LifeState life = Dead;
    int decay = 0;
};

class Grid {
    std::array<Cell, GRID_SIZE_3D> cells;

    std::optional<Cell> at_mut(int x, int y, int z) const;
    
public:
    Grid();
    
    const Cell& at(int x, int y, int z) const;
    void step(const SimRules&);
};
