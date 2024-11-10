#include "util.h"

std::string to_string(const Vector3 &v) {
    return "(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ")";
}

bool gt(float val, float base, float tolerance) {
    return val > base + tolerance;
}

bool lt(float val, float base, float tolerance) {
    return val < base - tolerance;
}

bool eq(float val, float base, float tolerance) {
    return base - tolerance <= val && val <= base + tolerance;
}