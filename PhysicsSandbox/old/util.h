#ifndef _MYUTIL_
#define _MYUTIL_

#define MYBLUE       CLITERAL(Color){ 0, 121, 241, 100 }
#define MYGREEN      CLITERAL(Color){ 0, 228, 48, 100 }
#define MYORANGE     CLITERAL(Color){ 255, 161, 0, 100 }
#define MYRED        CLITERAL(Color){ 230, 41, 55, 100 }

#include <vector>
#include <string>
#include "glm/vec3.hpp"
#include "glm/geometric.hpp"
#include "object3d.h"

std::string to_string(const glm::vec3 &v);

bool gt(float val, float base, float tolerance);
bool lt(float val, float base, float tolerance);
bool eq(float val, float base, float tolerance);

/*Vector3 operator+(const Vector3& v1, const Vector3& v2);
Vector3 operator-(const Vector3 &v1, const Vector3 &v2);
Vector3 operator*(float f, const Vector3 &v); */

std::vector<glm::vec3> RK4(const std::vector<glm::vec3> &statePrev, Object3D &ref, float h = 0.f, float time = 0.f);
/*
Probably not doing these because complicated matrix inversion for 3D vectors
- matrix addition, subtraction, multiplication
- jacobian
*/

void drawPlane(glm::vec3 &v0, glm::vec3 &v1, glm::vec3 &v2, glm::vec3 &v3);

#endif