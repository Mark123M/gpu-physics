#ifndef _PLANE_
#define _PLANE_
#include "raylib.h"
#include "raymath.h"
#include <string>

class Plane {
    float width, height;
    Vector3 origin, v1, v2, v3; // ccw from bottom left
    Vector3 normal;
public:
    Plane(Vector3 origin, Vector3 dir1, Vector3 dir2, float width, float height);
    void draw();

    std::string stringify();
    friend class Sphere;
};

#endif