#ifndef _PLANE_
#define _PLANE_

#include <string>
#include "raylib.h"
#include "raymath.h"
#include "util.h"
#include "collider.h"

class Plane: public Collider {
    float width, height;
    Vector3 origin, v1, v2, v3; // CCW from bottom left
    Vector3 normal;
public:
    Plane(Vector3 origin, Vector3 dir1, Vector3 dir2, float width, float height);
    void draw() override;

    std::string stringify() override;
    friend class Sphere;
};

#endif