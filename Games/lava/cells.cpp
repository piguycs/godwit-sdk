#include "cells.hpp"
#include "griditer.hpp"
#include <cassert>

void CellGrid::step(int size, SimRule rule) {
    update_queue.clear();
    
    for (auto [x,y,z] : XYZRange(size)) {
        const Cell& cell = at(x,y,z);
        int neighbours = count_alive_neighbours(x, y, z);

        switch (cell.life) {
            case Alive:
                if (neighbours != rule.remain_alive_threshold) {
                    // start the decay process for this cell
                    update_queue.push_back({x, y, z, Decaying});
                }
                break;
            case Dead:
                if (neighbours == rule.birth_threshold) {
                    update_queue.push_back({x, y, z, Alive});
                }
                break;
            case Decaying:
                update_queue.push_back({x, y, z, Decaying});
                break;
        }
    }

    for (auto update : update_queue) {
        Cell& cell = at_mut(update.x, update.y, update.z);
        if (update.alive == Alive) {
            cell.life = Alive;
            cell.decay = 0;
        } else if (update.alive == Decaying) {
            if (cell.life != Decaying) {
                cell.life = Decaying;
                cell.decay = rule.decay_start_value;
            } else {
                if (cell.decay > 0) cell.decay -= 1;
                if (cell.decay == 0) cell.life = Dead;
            }
        }
    }
}

int CellGrid::count_alive_neighbours(std::uint32_t x, std::uint32_t y, std::uint32_t z) const {
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
