#ifndef _SPHERE_
#define _SPHERE_

#include <iostream>
#include <vector>

#include "object3d.h"
#include "plane.h"
#include "logger.h"
#include "util.h"

class Sphere: public Object3D {
protected:
    float radius, mass, cAir, cRestitution, cFriction;
public:
    Sphere(float radius, float mass, glm::vec3 pos, glm::vec3 vel, float cAir, float cRestitution, float cFriction, std::vector<std::unique_ptr<Collider>> &colliders, FileLogger &logger);
    void integrate(float deltaTime);
    void collisionResponse(Plane &p); // GENERALIZE WITH COLLIDER FACE?
    std::vector<glm::vec3> F(const std::vector<glm::vec3> &S, float time) override;

    void update(float deltaTime) override;
    void draw() override;
    std::string stringify() override;
};

#endif
