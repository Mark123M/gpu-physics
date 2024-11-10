#ifndef _OBJECT_
#define _OBJECT_

#include <iostream>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "plane.h"
#include "logger.h"

class Object {
    std::vector<Vector3> state;
    std::vector<Vector3> state0; // initial states
    
    std::vector<Plane> &colliders;
    FileLogger &logger;
public:
    Object(std::vector<Vector3> &state0);
    virtual std::vector<Vector3> F(std::vector<Vector3> &S, float timestep, float time);
    virtual std::string stringify() = 0;
};

#endif
