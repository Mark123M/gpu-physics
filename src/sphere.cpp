#include "sphere.h"
#include "raylib.h"
#include "raymath.h"

const Vector3 GRAVITY{0, -10, 0};

Sphere::Sphere(float radius, float mass, Vector3 pos, Vector3 vel, float cAir, float cRestitution, float cFriction, std::vector<Plane> &colliders):
    radius{radius}, mass{mass}, cAir{cAir}, cRestitution{cRestitution}, cFriction{cFriction}, pos{pos}, vel{vel}, posPrev{pos}, velPrev{vel}, pos0{pos}, vel0{vel}, colliders{colliders}
{}

void Sphere::updateForce(float deltaTime) {
    force = Vector3Add(GRAVITY, Vector3Scale(vel, -cAir)); // air resistance
}

void Sphere::integrate(float deltaTime) {
    Vector3 accel = Vector3Scale(force, 1 / mass);
    vel = Vector3Add(velPrev, Vector3Scale(accel, deltaTime));
    pos = Vector3Add(posPrev, Vector3Scale(velPrev, deltaTime));
}

void collisionResponse(Plane &p) {

}

void Sphere::update(float deltaTime) {
    float timestepRemaining = deltaTime;

    while (timestepRemaining > 0) {
        updateForce(deltaTime);
        integrate(deltaTime);

        float minTimeFraction = 1.f;
        Plane *firstPlane = nullptr;
        for (Plane &p: colliders) {
            // abs distance from plane
            float dPrev = abs(Vector3DotProduct(Vector3Subtract(posPrev, p.origin), p.normal)) - radius;
            float d = abs(Vector3DotProduct(Vector3Subtract(pos, p.origin), p.normal)) - radius;
            
            // if parity is different, collision occurred
            if (dPrev > 0 != d > 0) {
                float timeFraction = dPrev / (dPrev + d);
                if (timeFraction < minTimeFraction) {
                    minTimeFraction = timeFraction;
                    firstPlane = &p;
                }
            }
        }
        if (firstPlane != nullptr) {
            integrate(minTimeFraction * timestepRemaining);
            collisionResponse(*firstPlane);
        }
        timestepRemaining -= minTimeFraction * timestepRemaining;
    }

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

std::string to_string(const Vector3 &v) {
    return "(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ")";
}

std::string Sphere::stringify() {
    return "[SPHERE] -> radius: " + std::to_string(radius) + ", mass: " + std::to_string(mass) + ", pos: " + to_string(pos) + ", vel: " + to_string(vel);
}
