#ifndef _OBJECT_
#define _OBJECT_

#include <iostream>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "plane.h"
#include "logger.h"

class Object3D {
protected:
    std::vector<Vector3> state;
    std::vector<Vector3> statePrev;
    std::vector<Vector3> state0; // Initial states
    
    std::vector<Plane> &colliders;
    FileLogger &logger;
public:
    Object3D(std::vector<Vector3> state0, std::vector<Plane> &colliders, FileLogger &logger);
    virtual std::vector<Vector3> F(const std::vector<Vector3> &S, float timestep) = 0;
    void reset();

    virtual void update(float deltaTime) = 0;
    virtual void draw();
    virtual std::string stringify() = 0;
};

#endif
