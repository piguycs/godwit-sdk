#include "grid.hpp"
#include "src/griditer.hpp"
#include <random>
#include <stdexcept>

static Cell EMPTY_CELL = {Dead, 0};

Grid::Grid() {
    std::mt19937 rng(42); // fixed seed
    std::uniform_real_distribution<float> dist(0.f, 1.f);
    constexpr float alive_percent = 0.05f;

    for (auto [x,y,z] : XYZRange(GRID_SIZE)) {
        Cell& cell = at_mut(x, y, z);
        
        if (dist(rng) < alive_percent) {
            cell.life = Alive;
            cell.decay = 0;
        }
    }
}

void Grid::step(const SimRules&) {
}

const Cell& Grid::at(int x, int y, int z) const {
    if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE || z < 0 || z >= GRID_SIZE) {
        // cells out of range are de-facto "dead"
        return EMPTY_CELL;
    };

    return {cells[x + y * GRID_SIZE + z * GRID_SIZE * GRID_SIZE]};
}

Cell& Grid::at_mut(int x, int y, int z) {
    if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE || z < 0 || z >= GRID_SIZE) {
        throw std::out_of_range("Grid::at_mut: out of bounds");
    };

    return cells[x + y * GRID_SIZE + z * GRID_SIZE * GRID_SIZE];
}

