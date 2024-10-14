#include "sphere.h"
#include "raylib.h"
#include "raymath.h"

Sphere::Sphere(float radius, float mass, Vector3 pos, Vector3 vel, float cAir, float cRestitution, float cFriction):
    radius{radius}, mass{mass}, cAir{cAir}, cRestitution{cRestitution}, cFriction{cFriction}, pos{pos}, vel{vel}, pos0{pos}, vel0{vel} {}

void Sphere::updateForce(float deltaTime) {

}
void Sphere::integrate(float deltaTime) {

}
void Sphere::update(float deltaTime) {
    updateForce(deltaTime);
    integrate(deltaTime);
}

std::ostream& operator<<(std::ostream& out, const Vector3 &v) {
    out << "(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
    return out;
}

std::ostream& operator<<(std::ostream& out, const Sphere &s) {
    out << "[SPHERE] -> radius: " << s.radius << ", mass: " << s.mass << ", pos: " << s.pos << ", vel: " << s.vel << std::endl;
    return out;  
}
