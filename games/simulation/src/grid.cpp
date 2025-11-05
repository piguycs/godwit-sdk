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

void Grid::step(const SimRules& rule) {
    updateQueue.clear();

    for (auto [x,y,z] : XYZRange(GRID_SIZE)) {
        const Cell& cell = at(x, y, z);
        int neighbours = count_alive_neighbours(x, y, z);

        switch (cell.life) {
            case Alive:
                if (!rule.stay[neighbours]) {
                    Update update{(int)x, (int)y, (int)z, Decaying};
                    updateQueue.push_back(update);
                }
                break;
                
            case Dead:
                if (rule.birth[neighbours]) {
                    Update update{(int)x, (int)y, (int)z, Alive};
                    updateQueue.push_back(update);
                }
                break;

            case Decaying:
                // keep decaying until death
                Update update{(int)x, (int)y, (int)z, Decaying};
                updateQueue.push_back(update);
                break;
        }

    }

    for (auto& update : updateQueue) {
        Cell& cell = at_mut(update.x, update.y, update.z);
        if (update.life == Alive) {
            cell.life = Alive;
            cell.decay = 0;
        } else if (update.life == Decaying) {
            if (cell.life != Decaying) {
                cell.life = Decaying;
                cell.decay = rule.decay_start;
            } else {
                if (cell.decay > 0) cell.decay -= 1;
                if (cell.decay == 0) cell.life = Dead;
            }
        }
    }
}

const Cell& Grid::at(int x, int y, int z) const {
    if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE || z < 0 || z >= GRID_SIZE) {
        // cells out of range are de-facto "dead"
        return EMPTY_CELL;
    };

    return {cells[x + y * GRID_SIZE + z * GRID_SIZE * GRID_SIZE]};
}

int Grid::count_alive_neighbours(int x, int y, int z) const {
    int count = 0;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dz = -1; dz <= 1; ++dz) {
                if (dx == 0 && dy == 0 && dz == 0) continue;
                if (dx == 0 && dy == 0 && dz == 0) continue;
                count += at(x + dx, y + dy, z + dz).life == Alive;
            }
        }
    }

    assert(count < 27);
    
    return count;
}

Cell& Grid::at_mut(int x, int y, int z) {
    if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE || z < 0 || z >= GRID_SIZE) {
        throw std::out_of_range("Grid::at_mut: out of bounds");
    };

    return cells[x + y * GRID_SIZE + z * GRID_SIZE * GRID_SIZE];
}

