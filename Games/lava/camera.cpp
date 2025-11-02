#include "camera.hpp"

namespace lava {

Camera::Camera(int grid_size, float radius)
    : radius(radius), cam_angle(0.f)
{
    float position = grid_size * 1.5f;
    float target = grid_size * 0.5f;
    
    // set up the defaults for the camera
    camera.position = {position, position, position};
    camera.target = {target, target, target};
    camera.up = {0,1,0};
    camera.fovy = DEFAULT_FOVY;
    camera.projection = CAMERA_PERSPECTIVE;
}

}
