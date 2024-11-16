#include "sphere.h"

const Vector3 GRAVITY{0, -10, 0};

Sphere::Sphere(float radius, float mass, Vector3 pos, Vector3 vel, float cAir, float cRestitution, float cFriction, std::vector<Plane> &colliders, FileLogger &logger):
    Object3D{std::vector<Vector3>{pos, vel}, colliders, logger}, radius{radius}, mass{mass}, cAir{cAir}, cRestitution{cRestitution}, cFriction{cFriction}, pos{pos}, vel{vel}, posPrev{pos}, velPrev{vel}, pos0{pos}, vel0{vel}, colliders{colliders}, logger{logger}
{}

void Sphere::updateForce(float deltaTime) {
    force = Vector3Add(GRAVITY, Vector3Scale(velPrev, -cAir)); // air resistance
}

void Sphere::collisionResponse(Plane &p) {
    Vector3 velN = Vector3Scale(p.normal, Vector3DotProduct(velPrev, p.normal));
    Vector3 velT = Vector3Subtract(velPrev, velN);
    vel = Vector3Add(Vector3Scale(velN, -cRestitution), Vector3Scale(velT, 1 - cFriction));
    logger.logToFile("  VELN: " + to_string(velN) + " VELT: " + to_string(velT));
}

std::vector<Vector3> Sphere::F(const std::vector<Vector3> &S, float time) {
    Vector3 vel = S[1];
    Vector3 accel = Vector3Scale(Vector3Add(GRAVITY, Vector3Scale(S[1], -cAir)), 1 / mass);
    return {vel, accel};
}

void Sphere::integrate(float deltaTime) {
   /* Vector3 accel = Vector3Scale(force, 1 / mass);
    vel = Vector3Add(velPrev, Vector3Scale(accel, deltaTime));
    pos = Vector3Add(posPrev, Vector3Scale(velPrev, deltaTime)); */
    state = RK4(statePrev, *this);
}

void Sphere::update(float deltaTime) {
    float timestepRemaining = deltaTime;

    while (timestepRemaining > 0) {
        velPrev = vel;
        posPrev = pos; 
        updateForce(timestepRemaining);
        integrate(timestepRemaining);
        logger.logToFile("START VELPREV: " + to_string(velPrev) + " START POSPREV: " + to_string(posPrev));
        float minTimeFraction = 1.f;
        Plane *firstPlane = nullptr;
        for (Plane &p: colliders) {
            // abs distance from plane
            float dPrev = abs(Vector3DotProduct(Vector3Subtract(posPrev, p.origin), p.normal)) - radius;
            float d = abs(Vector3DotProduct(Vector3Subtract(pos, p.origin), p.normal)) - radius;

            logger.logToFile("dPrev: " + std::to_string(dPrev) + " dCur: " + std::to_string(d));
            logger.logToFile("  DOT PRODUCT: " + std::to_string(Vector3DotProduct(velPrev, p.normal)));
            logger.logToFile("  PLANE: " + to_string(p.normal));
            // if parity is different, collision occurred
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
            updateForce(minTimeFraction * timestepRemaining);
            integrate(minTimeFraction * timestepRemaining);
            logger.logToFile("  COLLISION VELPREV: " + to_string(velPrev) + " COLLISION POSPREV: " + to_string(posPrev));
            collisionResponse(*firstPlane);
        }
        logger.logToFile("  " + stringify());
        timestepRemaining -= minTimeFraction * timestepRemaining;
    }

    logger.logToFile("FINAL STATE: " + stringify());
}

void Sphere::draw() {
    DrawSphere(pos, radius, RED);
    DrawSphereWires(pos, radius, 5, 5, BLACK);
}

std::string Sphere::stringify() {
    return "[SPHERE] -> radius: " + std::to_string(radius) + ", mass: " + std::to_string(mass) + ", pos: " + to_string(pos) + ", vel: " + to_string(vel);
}
