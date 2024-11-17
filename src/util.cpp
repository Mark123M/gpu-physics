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
    AddExpr(const L &l_, const R &r_): l{l_}, r{r_} {}
    Vector3 operator[](size_t i) const {
        return l[i] + r[i];
    }
    std::vector<Vector3> &vec() {
        v = std::vector<Vector3>(size());
        for (size_t i = 0; i < size(); i++) {
            v[i] = this->operator[](i);
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
    SubExpr(const L &l_, const R &r_): l{l_}, r{r_} {}
    Vector3 operator[](size_t i) const {
        return l[i] - r[i];
    }
    std::vector<Vector3> &vec() {
        v = std::vector<Vector3>(size());
        for (size_t i = 0; i < size(); i++) {
            v[i] = this->operator[](i);
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
    ScaleExpr(float k_, const R &r_): k{k_}, r{r_} {}
    Vector3 operator[](size_t i) const {
        return k * r[i];
    }
    std::vector<Vector3> &vec() {
        v = std::vector<Vector3>(size());
        for (size_t i = 0; i < size(); i++) {
            v[i] = this->operator[](i);
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

std::vector<Vector3> RK4(const std::vector<Vector3> &statePrev, Object3D &ref, float h, float time) {
    std::vector<Vector3> S = statePrev;

    std::vector<Vector3> K1 = ref.F(S, time);
    std::vector<Vector3> K2 = ref.F((S + (h / 2) * K1).vec(), time);
    std::vector<Vector3> K3 = ref.F((S + (h / 2) * K2).vec(), time);
    std::vector<Vector3> K4 = ref.F((S + h * K3).vec(), time);

    return (S + (h / 6) * (K1 + 2 * K2 + 2 * K3 + K4)).vec();
}