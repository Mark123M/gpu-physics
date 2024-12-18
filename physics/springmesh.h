#ifndef _SPRINGMESH_
#define _SPRINGMESH_

#include <iostream>
#include <vector>
#include <memory.h>
#include "object3d.h"
#include "plane.h"
#include "logger.h"
#include "util.h"

class Point: public Object3D {
protected:
    float mass;
    glm::vec3 force; // Accumulated force on the point: gravity, lift/drag, spring + damper
public:
    bool draw;
    Point(float mass, glm::vec3 pos, bool draw, std::vector<std::unique_ptr<Collider>> &colliders, FileLogger &logger);
    void integrate(float deltaTime);
    void collisionResponse(Plane &p);
    std::vector<glm::vec3> F(const std::vector<glm::vec3> &S, float time) override;

    void update(float deltaTime) override;
    const glm::vec3&getPos();
    const glm::vec3&getVel();
    std::string stringify() override;
};

struct Face {
    // int s1, s2, s3; // Spring indices
    Point &p1, p2, p3; // Use points if possible

    Face(Point& p1, Point& p2, Point& p3);
};

struct Spring {
    float k, d, l0;
    Point &p1, p2; // Points at the ends of springs
    bool draw;

    Spring(float k, float d, float l0, Point& p1, Point& p2, bool draw);
};

class SpringMesh: public Object3D {
protected:
    std::vector<Point> &points;
    std::vector<Spring> &springs;
    std::vector<Face> &faces;
public:
    SpringMesh(std::vector<Point> &points, std::vector<Spring> &springs, std::vector<Face> &faces, std::vector<std::unique_ptr<Collider>> &colliders, FileLogger &logger);
    std::vector<glm::vec3> F(const std::vector<glm::vec3> &S, float time) override;
    std::string stringify() override;
    void update(float deltaTime) override;
    void draw() override;
};

#endif
