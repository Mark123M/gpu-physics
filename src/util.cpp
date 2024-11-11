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

std::vector<Vector3> &operator+=(std::vector<Vector3> &v1, const std::vector<Vector3> &v2) {
    for (size_t i = 0; i < v1.size(); i++) {
        v1[i] = Vector3Add(v1[i], v2[i]);
    }
    return v1;
}

std::vector<Vector3> &operator-=(std::vector<Vector3> &v1, const std::vector<Vector3> &v2) {
    for (size_t i = 0; i < v1.size(); i++) {
        v1[i] = Vector3Subtract(v1[i], v2[i]);
    }
    return v1;
}

std::vector<Vector3> &operator*=(float k, std::vector<Vector3> &v) {
    for (size_t i = 0; i < v.size(); i++) {
        v[i] = Vector3Scale(v[i], k);
    }
    return v;
}

Vector3 operator+(const Vector3 &v1, const Vector3 &v2) {
    return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

Vector3 operator-(const Vector3 &v1, const Vector3 &v2) {
    return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

Vector3 operator*(float f, const Vector3 &v) {
    return {f * v.x, f * v.y, f * v.z};
}

template <typename L, typename R>
class AddExpr {
    const L &l;
    const R &r;
    std::vector<Vector3> v;
public:
    AddExpr(const L &l_, const R &r_): l{l_}, r{r_}, v{} {}
    Vector3 operator[](size_t i) const {
        return l[i] + r[i];
    }
    Vector3 &operator[](size_t i) {
        return l[i] + r[i];
    }
    std::vector<Vector3> &vec() {
        for (size_t i = 0; i < l.size(); i++) {
            v.push_back(this->operator[](i));
        }
        return v;
    }
    size_t size() {
        return l.size();
    }
};

template <typename L, typename R>
AddExpr<L, R> operator+(const L &l, const R &r) {
    return AddExpr<L, R>(l, r);
}

template <typename L, typename R>
class SubExpr {
    const L &l;
    const R &r;
    std::vector<Vector3> v;
public:
    SubExpr(const L &l_, const R &r_): l{l_}, r{r_}, v{} {}
    Vector3 operator[](size_t i) const {
        return l[i] - r[i];
    }
    Vector3 &operator[](size_t i) {
        return l[i] - r[i];
    }
    std::vector<Vector3> &vec() {
        for (size_t i = 0; i < l.size(); i++) {
            v.push_back(this->operator[](i));
        }
        return v;
    }
    size_t size() {
        return l.size();
    }
};

template <typename L, typename R>
SubExpr<L, R> operator-(const L &l, const R &r) {
    return SubExpr<L, R>(l, r);
}

template <typename R>
class ScaleExpr {
    float k;
    const R &r;
    std::vector<Vector3> v;
public:
    ScaleExpr(float k_, const R &r_): k{k_}, r{r_}, v{} {}
    Vector3 operator[](size_t i) const {
        return k * r[i];
    }
    Vector3 &operator[](size_t i) {
        return k * r[i];
    }
    std::vector<Vector3> &vec() {
        for (size_t i = 0; i < r.size(); i++) {
            v.push_back(this->operator[](i));
        }
        return v;
    }
    size_t size() {
        return r.size();
    }
};

template <typename R>
ScaleExpr<R> operator*(float k, const R &r) {
    return ScaleExpr<R>(k, r);
}

/*template <typename Expr>
std::vector<Vector3> &operator=(std::vector<Vector3> &state, Expr &&expr) {
    return state;
} */

// 1. conversion operator
// 2. precompute vector 
// 3. store vec representation to be computed eventually

std::vector<Vector3> RK4(const std::vector<Vector3> &statePrev, float timestep, float time, std::vector<Vector3> (&F)(std::vector<Vector3>&, float)) {
    std::vector<Vector3> S = statePrev;

    std::vector<Vector3> K1 = F(S, time);
    std::vector<Vector3> K2 = F((S + (timestep / 2) * K1).vec(), time);
}