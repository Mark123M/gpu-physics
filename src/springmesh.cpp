#include "springmesh.h"

Point::Point(float mass, Vector3 pos, std::vector<std::unique_ptr<Collider>> &colliders, FileLogger &logger):
    Object3D{{pos, Vector3{0, 0, 0}}, colliders, logger}, mass{mass} {}

void Point::integrate(float deltaTime) {
    state = RK4(statePrev, *this, deltaTime);
}

void Point::collisionResponse(Plane &p) {
}

std::vector<Vector3> Point::F(const std::vector<Vector3> &S, float time) {
    return S;
}

void Point::update(float deltaTime) {
}

const Vector3 &Point::getPos() {
    return state[0];
}

const Vector3 &Point::getVel() {
    return state[1];
}

std::string Point::stringify() {
    return std::string();
}

SpringMesh::SpringMesh(std::vector<Point> &points, std::vector<Spring> &springs, std::vector<Face> &faces, std::vector<std::unique_ptr<Collider>> &colliders, FileLogger &logger):
    Object3D{{}, colliders, logger}, points{points}, springs{springs}, faces{faces} {}

std::string SpringMesh::stringify() {
    return std::string();
}

void SpringMesh::update(float deltaTime) {
}

void SpringMesh::draw() {
    for (Face &f: faces) {
        const Vector3 &v1 = f.p1.getPos();
        const Vector3 &v2 = f.p2.getPos();
        const Vector3 &v3 = f.p3.getPos();
        
        DrawTriangle3D(v3, v2, v1, MYRED);
        DrawTriangle3D(v1, v2, v3, MYORANGE);
    }

    for (Spring &s: springs) {
        const Vector3 &v1 = s.p1.getPos();
        const Vector3 &v2 = s.p2.getPos();

        DrawLine3D(v1, v2, BLACK);
    }

    for (Point &p: points) {
        DrawPoint3D(p.getPos(), BLUE);
    }
}
