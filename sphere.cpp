#include "sphere.h"

using namespace glm;

const vec3 GRAVITY{0, -10, 0};

Sphere::Sphere(float radius, float mass, vec3 pos, vec3 vel, float cAir, float cRestitution, float cFriction, std::vector<std::unique_ptr<Collider>> &colliders, FileLogger &logger):
    Object3D{std::vector<vec3>{pos, vel}, colliders, logger}, radius{radius}, mass{mass}, cAir{cAir}, cRestitution{cRestitution}, cFriction{cFriction}
{
    std::vector<vec3> test = RK4(state, *this);
    for (vec3 &v: test) {
        logger.logToFile(to_string(v));
    }

    logger.logToFile("=============================================================================FINISHED CONSTRUCTOR");

}

void Sphere::collisionResponse(Plane &p) {
    vec3 velN = dot(statePrev[1], p.normal) * p.normal;
    vec3 velT = statePrev[1] - velN;
    state[1] = -cRestitution * velN + (1 - cFriction) * velT;
    logger.logToFile("  VELN: " + to_string(velN) + " VELT: " + to_string(velT));
}

std::vector<vec3> Sphere::F(const std::vector<vec3> &S, float time) {
    //logger.logToFile("IN: " + to_string(S[0]) + " " + to_string(S[1]));
    vec3 vel = S[1];
    vec3 accel = (1 / mass) * (GRAVITY - cAir * S[1]);
    //logger.logToFile("OUT: " + to_string(vel) + " " + to_string(accel));
    return {vel, accel};
}

void Sphere::integrate(float deltaTime) {
   /* Vector3 accel = Vector3Scale(force, 1 / mass);
    vel = Vector3Add(velPrev, Vector3Scale(accel, deltaTime));
    pos = Vector3Add(posPrev, Vector3Scale(velPrev, deltaTime)); */
    state = RK4(statePrev, *this, deltaTime);
}

void Sphere::update(float deltaTime) {
    float timestepRemaining = deltaTime;

    while (timestepRemaining > 0) {
        statePrev = state;
        
        integrate(timestepRemaining);
        logger.logToFile("START VELPREV: " + to_string(statePrev[1]) + " START POSPREV: " + to_string(statePrev[0]));
        float minTimeFraction = 1.f;
        Plane *firstPlane = nullptr;

        // @todo Each collider could return CollisionData (didCollide, collisionPoint etc.)
        for (auto &c: colliders) {
            Plane &p = dynamic_cast<Plane&>(*c);

            // Abs distance from plane
            float dPrev = abs(dot(statePrev[0] - p.origin, p.normal)) - radius;
            float d = abs(dot(state[0] - p.origin, p.normal)) - radius;

            logger.logToFile("dPrev: " + std::to_string(dPrev) + " dCur: " + std::to_string(d));
            logger.logToFile("  DOT PRODUCT: " + std::to_string(dot(statePrev[1], p.normal)));
            logger.logToFile("  PLANE: " + to_string(p.normal));
            // If parity is different, collision occurred
            if (!eq(dPrev, 0, 0.0005) && dPrev > 0 != d > 0) {
                float timeFraction = abs(dPrev) / (abs(dPrev) + abs(d));
                if (timeFraction < minTimeFraction) {
                    minTimeFraction = timeFraction;
                    firstPlane = &p;
                }
            }
        }
        logger.logToFile("  time remaining: " + std::to_string(timestepRemaining) + " time fraction: " + std::to_string(minTimeFraction));
        if (firstPlane != nullptr) {
            integrate(minTimeFraction * timestepRemaining);
            logger.logToFile("  COLLISION VELPREV: " + to_string(statePrev[1]) + " COLLISION POSPREV: " + to_string(statePrev[0]));
            collisionResponse(*firstPlane);
        }
        logger.logToFile("  " + stringify());
        timestepRemaining -= minTimeFraction * timestepRemaining;
    }

    logger.logToFile("FINAL STATE: " + stringify());
}

void Sphere::draw() {
    // FUCK
}

std::string Sphere::stringify() {
    return "[SPHERE] -> radius: " + std::to_string(radius) + ", mass: " + std::to_string(mass) + ", pos: " + to_string(state[0]) + ", vel: " + to_string(state[1]);
}
