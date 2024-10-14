#ifndef _PLANE_
#define _PLANE_
#include "raylib.h"
#include "raymath.h"

class Plane {
    float width, height;
    Vector3 origin;
    Vector3 dir1, dir2;
    Vector3 normal, v1, v2, v3, v4;  // clock-wise from top left
public:
    Plane(Vector3 origin, Vector3 dir1, Vector3 dir2, float width, float height);
    void update(float deltaTime);
};

#endif