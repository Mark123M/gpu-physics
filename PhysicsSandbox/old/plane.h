#ifndef _PLANE_
#define _PLANE_

#include "util.h"
#include "collider.h"

class Plane: public Collider {
    float width, height;
    glm::vec3 origin, v1, v2, v3; // CCW from bottom left
    glm::vec3 normal;
public:
    Plane(glm::vec3 origin, glm::vec3 dir1, glm::vec3 dir2, float width, float height);
    void draw() override;

    std::string stringify() override;
    friend class Sphere;
};

#endif