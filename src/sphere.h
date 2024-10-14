#ifndef _SPHERE_
#define _SPHERE_
#include "raylib.h"
#include "raymath.h"
#include <iostream>

class Sphere {
    float radius, mass, cAir, cRestitution, cFriction;
    Vector3 pos, vel, posPrev, velPrev, force;
    const Vector3 pos0, vel0; // initial states
public:
    Sphere(float radius, float mass, Vector3 pos, Vector3 vel, float cAir, float cRestitution, float cFriction);
    void updateForce(float deltaTime);
    void integrate(float deltaTime);
    void update(float deltaTime);
    void draw();
    void reset();
    std::string stringify();
};

#endif
