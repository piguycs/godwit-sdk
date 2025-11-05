#include "grid.hpp"

static Cell EMPTY_CELL = {Dead, 0};

Grid::Grid() {
}

const Cell& Grid::at(int x, int y, int z) const {
    if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE || z < 0 || z >= GRID_SIZE) {
        // cells out of range are de-facto "dead"
        return EMPTY_CELL;
    };

    return {cells[x + y * GRID_SIZE + z * GRID_SIZE * GRID_SIZE]};
}

void Grid::step(const SimRules&) {
}
