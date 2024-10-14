#include "plane.h"
#include "raylib.h"
#include "raymath.h"

Plane::Plane(Vector3 origin, Vector3 dir1, Vector3 dir2, float width, float height): width{width}, height{height}, origin{origin}, v1{Vector3Add(origin, Vector3Scale(dir1, width))},
    v2{Vector3Add(v1, Vector3Scale(dir2, height))}, v3{Vector3Add(origin, Vector3Scale(dir2, height))}, normal{Vector3CrossProduct(dir1, dir2)} {}

void Plane::draw() {
    // draw 2 triangles representing the plane
    DrawTriangle3D(v3, v1, origin, GREEN);
    DrawTriangle3D(v3, v2, v1, GREEN);
}