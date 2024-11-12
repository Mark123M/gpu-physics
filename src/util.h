#ifndef _MYUTIL_
#define _MYUTIL_

#include <vector>
#include <string>
#include "raymath.h"

std::string to_string(const Vector3 &v);

bool gt(float val, float base, float tolerance);
bool lt(float val, float base, float tolerance);
bool eq(float val, float base, float tolerance);

Vector3 operator+(const Vector3 &v1, const Vector3 &v2);
Vector3 operator-(const Vector3 &v1, const Vector3 &v2);
Vector3 operator*(float f, const Vector3 &v);

std::vector<Vector3> RK4(const std::vector<Vector3> &statePrev, float h, float time, std::vector<Vector3> (&F)(std::vector<Vector3>&, float));
/*
Probably not doing these because complicated matrix inversion for 3D vectors
- matrix addition, subtraction, multiplication
- jacobian
*/

#endif