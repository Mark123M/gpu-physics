#include "plane.h"
#include "raylib.h"
#include "raymath.h"

Plane::Plane(Vector3 origin, Vector3 dir1, Vector3 dir2, float width, float height): width{width}, height{height}, origin{origin}, dir1{dir1}, dir2{dir2} {
    normal = Vector3CrossProduct(dir1, dir2);
    // calculate v1-v4 based on width and height
}

void Plane::update(float deltaTime) {
    // draw 2 triangles representing the plane
}