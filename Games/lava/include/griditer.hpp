#pragma once

#include <cstdint>
#include <tuple>

/*!
* Iterate over x-y-z coordinates within the given width/height/depth parameters
*
* \code
* for (auto [x,y,z] : XYZRange(WIDTH, HEIGHT, DEPTH)) {
*     if (dist(rng) < alive_percent) {
*         grid.set_alive_at(x, y, z, true);
*     }
* }
* \endcode
* 
*/
struct XYZIterator {
    std::uint32_t width, height, depth;
    std::uint32_t x=0, y=0, z=0;

    XYZIterator(std::uint32_t w, std::uint32_t h, std::uint32_t d, std::uint32_t start_z=0) : 
        width(w), height(h), depth(d), z(start_z) {}

    bool operator!=(const XYZIterator& other) const {
        return z != other.z;
    }

    void operator++() {
        x++;
        if (x >= width) { x = 0; y++; }
        if (y >= height) { y = 0; z++; }
    }

    std::tuple<std::uint32_t,std::uint32_t,std::uint32_t> operator*() const { return {x,y,z}; }
};

struct XYZRange {
    std::uint32_t width, height, depth;
    XYZRange(std::uint32_t w, std::uint32_t h, std::uint32_t d) : width(w), height(h), depth(d) {}
    XYZIterator begin() const { return {width, height, depth, 0}; }
    XYZIterator end() const { return {width, height, depth, depth}; }
};
