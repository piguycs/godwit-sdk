#pragma once

#include <cstdint>
#include <stdexcept>
#include <vector>

struct Cell {
    std::uint32_t state = 10;
    bool alive;
};

struct CellGrid {
    std::vector<Cell> cells;

    std::uint32_t width;
    std::uint32_t height;
    std::uint32_t depth;

public:
    static CellGrid init(std::uint32_t width, std::uint32_t height, std::uint32_t depth) {
        std::vector<Cell> cells;
        // fill the vector with default values
        cells.resize(width * height * depth);
        return CellGrid{ cells, width, height, depth };
    }

    const Cell& at(std::uint32_t x, std::uint32_t y, std::uint32_t z) const {
        static const Cell dead_cell{0,false};
        if (x >= width || y >= height || z >= depth) {
            // anything outside the grid is dead
            return dead_cell;
        }
        
        return cells[x + y * width + z * width * height];
    }

    void set_alive_at(std::uint32_t x, std::uint32_t y, std::uint32_t z, bool alive) {
        if (x >= width || y >= height || z >= depth) {
            throw std::out_of_range("CellGrid::at");
        }
        
        cells[x + y * width + z * width * height].alive = alive;
    }

    void set_state_at(std::uint32_t x, std::uint32_t y, std::uint32_t z, std::uint32_t state) {
        if (x >= width || y >= height || z >= depth) {
            throw std::out_of_range("CellGrid::at");
        }
        
        cells[x + y * width + z * width * height].state = state;
    }

    int count_alive_neighbours(std::uint32_t x, std::uint32_t y, std::uint32_t z) const {
        int count = 0;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dz = -1; dz <= 1; ++dz) {
                    if (dx == 0 && dy == 0 && dz == 0) continue;
                    if (dx == 0 && dy == 0 && dz == 0) continue;
                    count += at(x + dx, y + dy, z + dz).alive;
                }
            }
        }
        
        return count;
    }

    void step() {
    }
};
