#ifndef _MYUTIL_
#define _MYUTIL_

#include <vector>
#include <string>
#include "raymath.h"

std::string to_string(const Vector3 &v);

bool gt(float val, float base, float tolerance);
bool lt(float val, float base, float tolerance);
bool eq(float val, float base, float tolerance);

std::vector<Vector3> operator+(const std::vector<Vector3> &v1, const std::vector<Vector3> &v2);
std::vector<Vector3> operator-(const std::vector<Vector3> &v1, const std::vector<Vector3> &v2);

/*
Probably not doing these because complicated matrix inversion for 3D vectors
- matrix addition, subtraction, multiplication
- jacobian
*/

#endif