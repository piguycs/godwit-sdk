#pragma once

#include "src/rules.hpp"
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

struct Update {
    int x, y, z;
    LifeState life;
};

class Grid {
    std::array<Cell, GRID_SIZE_3D> cells;
    std::vector<Update> updateQueue;

    // WILL THROW AN EXCEPTION IF OUT OF BOUNDS, FOR INTERNAL USE ONLY
    Cell& at_mut(int x, int y, int z);
    
public:
    Grid();
    
    const Cell& at(int x, int y, int z) const;
    int count_alive_neighbours(int x, int y, int z) const;

    void step(const SimRules&);
};
