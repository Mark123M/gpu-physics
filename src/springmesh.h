#ifndef _SPRINGMESH_
#define _SPRINGMESH_

#include <iostream>
#include <vector>
#include <memory.h>
#include "raylib.h"
#include "raymath.h"
#include "object3d.h"
#include "plane.h"
#include "logger.h"
#include "util.h"

class Point: public Object3D {
protected:
    float mass;
    Vector3 force; // Accumulated force on the point: gravity, lift/drag, spring + damper
public:
    Point(float mass, Vector3 pos, std::vector<std::unique_ptr<Collider>> &colliders, FileLogger &logger);
    void integrate(float deltaTime);
    void collisionResponse(Plane &p);
    std::vector<Vector3> F(const std::vector<Vector3> &S, float time) override;

    void update(float deltaTime) override;
    const Vector3 &getPos();
    const Vector3 &getVel();
    std::string stringify() override;
};

struct Face {
    int s1, s2, s3; // Spring indices
    Point &p1, p2, p3; // Use points if possible
};

struct Spring {
    float k, d, l0;
    Point &p1, p2; // Points at the ends of springs
    // Face &f1, f2;
};

class SpringMesh: public Object3D {
protected:
    std::vector<Point> &points;
    std::vector<Spring> &springs;
    std::vector<Face> &faces;
public:
    SpringMesh(std::vector<Point> &points, std::vector<Spring> &springs, std::vector<Face> &faces, std::vector<std::unique_ptr<Collider>> &colliders, FileLogger &logger);

    std::string stringify();
    void update(float deltaTime) override;
    void draw() override;
};

#endif
