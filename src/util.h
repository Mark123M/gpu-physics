#ifndef _MYUTIL_
#define _MYUTIL_

#define MYBLUE       CLITERAL(Color){ 0, 121, 241, 100 }
#define MYGREEN      CLITERAL(Color){ 0, 228, 48, 100 }
#define MYORANGE     CLITERAL(Color){ 255, 161, 0, 100 }
#define MYRED        CLITERAL(Color){ 230, 41, 55, 100 }

#include <vector>
#include <string>
#include "raylib.h"
#include "raymath.h"
#include "object3d.h"

std::string to_string(const Vector3 &v);

bool gt(float val, float base, float tolerance);
bool lt(float val, float base, float tolerance);
bool eq(float val, float base, float tolerance);

Vector3 operator+(const Vector3 &v1, const Vector3 &v2);
Vector3 operator-(const Vector3 &v1, const Vector3 &v2);
Vector3 operator*(float f, const Vector3 &v);

std::vector<Vector3> RK4(const std::vector<Vector3> &statePrev, Object3D &ref, float h = 0.f, float time = 0.f);
/*
Probably not doing these because complicated matrix inversion for 3D vectors
- matrix addition, subtraction, multiplication
- jacobian
*/

void drawPlane(Vector3 &v0, Vector3 &v1, Vector3 &v2, Vector3 &v3);

#endif