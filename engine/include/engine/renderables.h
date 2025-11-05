#pragma once

namespace engine {

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
    float width, height, depth;
    float x, y, z;
    // TODO: color without exposing raylib.h
public:
    CubeRender(float width, float height, float depth, float x, float y, float z)
        : width(width), height(height), depth(depth), x(x), y(y), z(z)
    {
    }

    void renderFunction() override;
};

class FpsRender: public IRenderable2D {
    int x;
    int y;

public:
    FpsRender(int x, int y): x(x), y(y) {}
    void renderFunction() override;
};

class ClearBackgroundRender: public IRenderable2D {
public:
    ClearBackgroundRender() {}
    void renderFunction() override;
};

}
