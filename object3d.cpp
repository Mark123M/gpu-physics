#include "object3d.h"

Object3D::Object3D(std::vector<glm::vec3> state0, std::vector<std::unique_ptr<Collider>> &colliders, FileLogger &logger):
    state{state0}, statePrev{state0}, state0{state0}, colliders{colliders}, logger{logger} {}

void Object3D::reset() {
    state = state0;
    statePrev = state0;
}

void Object3D::draw() {}