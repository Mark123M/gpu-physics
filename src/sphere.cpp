#include "sphere.h"
#include "raylib.h"
#include "raymath.h"

const Vector3 GRAVITY{0, -10, 0};

Sphere::Sphere(float radius, float mass, Vector3 pos, Vector3 vel, float cAir, float cRestitution, float cFriction):
    radius{radius}, mass{mass}, cAir{cAir}, cRestitution{cRestitution}, cFriction{cFriction}, pos{pos}, vel{vel}, posPrev{pos}, velPrev{vel}, pos0{pos}, vel0{vel}
{}

void Sphere::updateForce(float deltaTime) {
    force = Vector3Add(GRAVITY, Vector3Scale(vel, -cAir)); // air resistance
}

void Sphere::integrate(float deltaTime) {
    Vector3 accel = Vector3Scale(force, 1 / mass);
    vel = Vector3Add(velPrev, Vector3Scale(accel, deltaTime));
    pos = Vector3Add(posPrev, Vector3Scale(velPrev, deltaTime));
}

void Sphere::update(float deltaTime) {
    updateForce(deltaTime);
    integrate(deltaTime);

    velPrev = vel;
    posPrev = pos; 
}

void Sphere::draw() {
    DrawSphere(pos, radius, RED);
    DrawSphereWires(pos, radius, 5, 5, BLACK);
}

void Sphere::reset() {
    vel = vel0;
    pos = pos0;
    velPrev = vel0;
    posPrev = pos0; 
}

std::ostream& operator<<(std::ostream& out, const Vector3 &v) {
    out << "(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
    return out;
}

std::ostream& operator<<(std::ostream& out, const Sphere &s) {
    out << "[SPHERE] -> radius: " << s.radius << ", mass: " << s.mass << ", pos: " << s.pos << ", vel: " << s.vel << std::endl;
    return out;  
}
