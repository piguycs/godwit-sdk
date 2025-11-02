#pragma once

#include "src/rules.hpp"
#include <vector>

enum LifeState {
    Dead,
    Alive,
    Decaying,
};

struct Cell {
    LifeState life;
    int decay;
};

class Grid {
    std::vector<Cell> cells;
public:
    void step(const SimRules&);
};
