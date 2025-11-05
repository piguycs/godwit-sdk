#pragma once

#include <cstdint>

namespace engine {

/*!
* Red Green Blue colours
*/
struct RGB{uint8_t r,g,b;};

/*!
* Represent coordinates on a 2 dimensional
*/
struct Position2D {float x, y;};

/*!
* Represent coordinates on a 3 dimensional
*/
struct Position3D {
    float x, y, z;
    Position3D(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct Scale{
    float width, height, depth;
    Scale(float width, float height, float depth)
        : width(width), height(height), depth(depth) {}
};

class IRenderable2D {
public:
    virtual void renderFunction() = 0;
    virtual ~IRenderable2D() = default;
};

class IRenderable3D {
public:
    virtual void renderFunction() = 0;
    virtual ~IRenderable3D() = default;
};

class CubeRender: public IRenderable3D {
    Scale scale;
    Position3D position;
    RGB colour;
public:
    CubeRender(Scale scale, Position3D position, RGB colour)
        : scale(scale), position(position), colour(colour) {}

    void renderFunction() override;
};

class FpsRender: public IRenderable2D {
    int x, y;

public:
    FpsRender(int x, int y): x(x), y(y) {}
    void renderFunction() override;
};

class ClearBackgroundRender: public IRenderable2D {
    RGB colour;
public:
    ClearBackgroundRender(RGB colour): colour(colour) {}
    void renderFunction() override;
};

}
