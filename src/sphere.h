#ifndef _SPHERE_
#define _SPHERE_
#include "raylib.h"
#include "raymath.h"
#include "plane.h"
#include <iostream>
#include <vector>

class Sphere {
    float radius, mass, cAir, cRestitution, cFriction;
    Vector3 pos, vel, posPrev, velPrev, force;
    const Vector3 pos0, vel0; // initial states
    
    std::vector<Plane> &colliders;
public:
    Sphere(float radius, float mass, Vector3 pos, Vector3 vel, float cAir, float cRestitution, float cFriction, std::vector<Plane> &colliders);
    void updateForce(float deltaTime);
    void integrate(float deltaTime);
    void collisionResponse(Plane &p);
    void update(float deltaTime);
    void draw();

    void reset();
    void setColliders(std::vector<Plane> &colliders);

    std::string stringify();
};

#endif
