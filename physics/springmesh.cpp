#include "springmesh.h"

using namespace glm;

Point::Point(float mass, vec3 pos, bool draw, std::vector<std::unique_ptr<Collider>> &colliders, FileLogger &logger):
    Object3D{ {pos, vec3{0, 0, 0}}, colliders, logger }, mass{ mass }, draw{ draw }, force{ glm::vec3{0, 0, 0} } {
}

void Point::integrate(float deltaTime) {
    state = RK4(statePrev, *this, deltaTime);
}

void Point::collisionResponse(Plane &p) {
}

std::vector<vec3> Point::F(const std::vector<vec3> &S, float time) {
    return S;
}

void Point::update(float deltaTime) {
}

const vec3 &Point::getPos() {
    return state[0];
}

const vec3 &Point::getVel() {
    return state[1];
}

std::string Point::stringify() {
    return std::string();
}

SpringMesh::SpringMesh(std::vector<Point> &points, std::vector<Spring> &springs, std::vector<Face> &faces, std::vector<std::unique_ptr<Collider>> &colliders, FileLogger &logger):
    Object3D{{}, colliders, logger}, points{points}, springs{springs}, faces{faces} {}

std::vector<vec3> SpringMesh::F(const std::vector<vec3> &S, float time)
{
    return std::vector<vec3>();
}

std::string SpringMesh::stringify() {
    return "[SpringMesh] -> # of points: " + std::to_string(points.size()) + " # of springs: " + std::to_string(springs.size()) + " # of faces: " + std::to_string(faces.size());
}

void SpringMesh::update(float deltaTime) {
}

void SpringMesh::draw() {
    /*for (Face &f: faces) {
        const Vector3 &v1 = f.p1.getPos();
        const Vector3 &v2 = f.p2.getPos();
        const Vector3 &v3 = f.p3.getPos();
        
        DrawTriangle3D(v3, v2, v1, MYRED);
        DrawTriangle3D(v1, v2, v3, MYORANGE);
    }*/

    for (Spring &s: springs) {
        if (s.draw) {
            const vec3 &v1 = s.p1.getPos();
            const vec3 &v2 = s.p2.getPos();
            //DrawLine3D(v1, v2, BLACK);
            //logger.logToFile("WHAT THE FUCK SPRING " + to_string(v1) + " " + to_string(v2));
        }
    }

    for (Point &p: points) {
        if (p.draw) {
            //DrawSphere(p.getPos(), 0.025, RED);
            //logger.logToFile("WHAT THE FUCK POINT " + to_string(p.getPos()));
        }
    }
}

Face::Face(Point& p1, Point& p2, Point& p3): p1{p1}, p2{p2}, p3{p3} {}

Spring::Spring(float k, float d, float l0, Point& p1, Point& p2, bool draw): k{k}, d{d}, l0{l0}, p1{p1}, p2{p2}, draw{draw} {}
