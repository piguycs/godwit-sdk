#pragma once

#include <raylib.h>

// begin raylib 3d draw mode, and then end it when this is destructed
// TODO: this is probably not safe to be moved around? I will need to add the move/copy constructors
struct DrawHandle3D {
    DrawHandle3D(Camera3D camera) { BeginMode3D(camera); }
    ~DrawHandle3D() { EndMode3D(); }
};
