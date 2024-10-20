#include <vector>
#include "raymath.h"
#ifndef _MYMATH_
#define _MYMATH_

std::vector<Vector3> operator+(const std::vector<Vector3> &v1, const std::vector<Vector3> &v2);

std::vector<Vector3> operator-(const std::vector<Vector3> &v1, const std::vector<Vector3> &v2);

/*
Probably not doing these because complicated matrix inversion for 3D vectors
- matrix addition, subtraction, multiplication
- jacobian
*/

#endif