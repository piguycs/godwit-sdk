#include "cells.hpp"
#include "griditer.hpp"
#include <cassert>

void CellGrid::step(int size, SimRule rule) {
    update_queue.clear();
    
    for (auto [x,y,z] : XYZRange(size)) {
        const Cell& cell = at(x,y,z);
        int neighbours = count_alive_neighbours(x, y, z);

        if (cell.life == Alive && neighbours == rule.remain_alive_threshold) {
            // it stays alive
        } else if (cell.life == Dead && neighbours == rule.birth_threshold) {
            update_queue.push_back({x,y,z,Alive});
        } else {
            update_queue.push_back({x,y,z,Dead});
        }
    }

    for (auto update : update_queue) {
        set_life_at(update.x, update.y, update.z, update.alive);
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
