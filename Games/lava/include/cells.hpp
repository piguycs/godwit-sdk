#pragma once

#include <cstdint>
#include <stdexcept>
#include <vector>
#include "simrule.hpp"

enum Life {
    Dead,
    Alive,
    StartedDecay,
};

struct Update {
    std::uint32_t x, y, z;
    Life alive;
};

struct Cell {
    std::uint32_t decay = 10;
    Life life;
};

class CellGrid {
    std::vector<Cell> cells;

    std::vector<Update> update_queue;

    std::uint32_t width;
    std::uint32_t height;
    std::uint32_t depth;

public:
    static CellGrid init(std::uint32_t size) {
        return CellGrid(size);
    }

    const Cell& at(std::uint32_t x, std::uint32_t y, std::uint32_t z) const {
        static const Cell dead_cell{0,Dead};
        if (x >= width || y >= height || z >= depth) {
            // anything outside the grid is dead
            return dead_cell;
        }
        
        return cells[x + y * width + z * width * height];
    }

    void set_life_at(std::uint32_t x, std::uint32_t y, std::uint32_t z, Life life) { at_mut(x,y,z).life = life; }
    void set_decay_at(std::uint32_t x, std::uint32_t y, std::uint32_t z, std::uint32_t decay) { at_mut(x,y,z).decay = decay; }

    int count_alive_neighbours(std::uint32_t x, std::uint32_t y, std::uint32_t z) const; 
    void step(int size, SimRule rule);

private:
    Cell& at_mut(std::uint32_t x, std::uint32_t y, std::uint32_t z) {
        if (x >= width || y >= height || z >= depth) {
            throw std::out_of_range("CellGrid::at");
        }
        
        return cells[x + y * width + z * width * height];
    }

    CellGrid(std::uint32_t size): width(size), height(size), depth(size) {
        cells.resize(width * height * depth);
        update_queue.resize(width * height * depth);
    }
};
