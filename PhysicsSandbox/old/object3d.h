#ifndef _OBJECT3D_
#define _OBJECT3D_

#include <iostream>
#include <vector>
#include <memory>
#include "collider.h"
#include "logger.h"
#include "glm/vec3.hpp"
#include "glm/geometric.hpp"

class Object3D {
protected:
    std::vector<glm::vec3> state;
    std::vector<glm::vec3> statePrev;
    std::vector<glm::vec3> state0; // Initial states
    
    std::vector<std::unique_ptr<Collider>> &colliders;
    FileLogger &logger;
public:
    Object3D(std::vector<glm::vec3> state0, std::vector<std::unique_ptr<Collider>> &colliders, FileLogger &logger);
    virtual std::vector<glm::vec3> F(const std::vector<glm::vec3> &S, float timestep) = 0;
    void reset();

    virtual void update(float deltaTime) = 0;
    virtual void draw();
    virtual std::string stringify() = 0;
};

#endif
