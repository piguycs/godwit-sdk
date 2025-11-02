#pragma once

#include <cmath>
#include "raylib.h"

// namespace here so that we dont clash with raylib's camera
namespace lava {

const float DEFAULT_FOVY = 60.0f;

class Camera {
    Camera3D camera;
    float radius;
    float cam_angle;

public:
    Camera(int grid_size, float radius);
    Camera3D& rlCam3d() { return camera; }

    float rotate(float rotation_speed, int grid_size) {
        cam_angle += rotation_speed;

        camera.position.x = grid_size/2.f + radius * std::cos(cam_angle);
        camera.position.z = grid_size/2.f + radius * std::sin(cam_angle);
        camera.position.y = grid_size;

        return 0.0;
    }
};

}
