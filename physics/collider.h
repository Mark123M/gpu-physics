#ifndef _COLLIDER_
#define _COLLIDER_

#include <string>
#include "glm/vec3.hpp"
#include "glm/geometric.hpp"

class Collider {
public:
    virtual void draw();
    virtual std::string stringify();
};

#endif