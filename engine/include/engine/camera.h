#pragma once

namespace engine {

// each camera needs to have a unique type due to our resource manager
// so we would use templates for that. I know rust has const geerics, idk c++
struct Camera {
    // position
    float posX, posY, posZ;
    // target
    float targetX, targetY, targetZ;
    // up
    float upX, upY, upZ;
    float fovy;

    Camera(
        // HACK: these are WAYY to many arguments, I would prefer to instead "reexport" raylib's
        // vector types, so that the game code can use those vectors without introducing ALL or
        // raylib.h into their imports
        float posX, float posY, float posZ,
        float targetX, float targetY, float targetZ,
        float upX, float upY, float upZ,
        float fovy
    )
        : posX(posX), posY(posY), posZ(posZ),
          targetX(targetX), targetY(targetY), targetZ(targetZ),
          upX(upX), upY(upY), upZ(upZ),
          fovy(fovy)
    {
    }

};

}
