#ifndef _SPHERE_
#define _SPHERE_

#include <iostream>
#include <vector>

#include "raylib.h"
#include "raymath.h"
#include "object3d.h"
#include "plane.h"
#include "logger.h"
#include "util.h"

class Sphere: public Object3D {
    float radius, mass, cAir, cRestitution, cFriction;
    Vector3 pos, vel, posPrev, velPrev, force;
    const Vector3 pos0, vel0; // initial states
    
    std::vector<Plane> &colliders;
    FileLogger &logger;
public:
    Sphere(float radius, float mass, Vector3 pos, Vector3 vel, float cAir, float cRestitution, float cFriction, std::vector<Plane> &colliders, FileLogger &logger);
    void updateForce(float deltaTime);
    void integrate(float deltaTime);
    void collisionResponse(Plane &p);
    std::vector<Vector3> F(std::vector<Vector3> &S, float time) override;

    void update(float deltaTime) override;
    void draw() override;
    std::string stringify() override;
};

#endif
