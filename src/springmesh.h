#ifndef _SPRINGMESH_
#define _SPRINGMESH_

#include <iostream>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "plane.h"
#include "logger.h"

class SpringMesh {
    FileLogger &logger;
public:
    SpringMesh(std::vector<Plane> &colliders, FileLogger &logger);

    std::string stringify();
};

#endif
