#pragma once

#include <cmath>
#include <iostream>
#include "ray_tracing_in_one_weekend.h"

class Vec3
{
public:
    Vec3() : e_{0, 0, 0} {}
    Vec3(double e0, double e1, double e2) : e_{e0, e1, e2} {}

    double x() const { return e_[0]; }
    double y() const { return e_[1]; }
    double z() const { return e_[2]; }

    Vec3 operator-() const { return Vec3(-e_[0], -e_[1], -e_[2]); }
    double operator[](int i) const { return e_[i]; }
    double &operator[](int i) { return e_[i]; }

    Vec3 &operator+=(const Vec3 &v)
    {
        e_[0] += v.e_[0];
        e_[1] += v.e_[1];
        e_[2] += v.e_[2];
        return *this;
    }

    Vec3 &operator*=(const double t)
    {
        e_[0] *= t;
        e_[1] *= t;
        e_[2] *= t;
        return *this;
    }

    Vec3 &operator/=(const double t)
    {
        return *this *= 1 / t;
    }

    double length() const
    {
        return std::sqrt(length_squared());
    }

    double length_squared() const
    {
        return e_[0] * e_[0] + e_[1] * e_[1] + e_[2] * e_[2];
    }

    inline static Vec3 random() {
        return Vec3(random_double(), random_double(), random_double());
    }

    inline static Vec3 random(double min, double max) {
        return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

    bool near_zero() const {
        const auto eps = 1e-8;
        return (fabs(e_[0]) < eps) && (fabs(e_[1]) < eps) && (fabs(e_[2]) < eps);
    } 

public:
    double e_[3];
};

using Point3 = Vec3;
using Color = Vec3;

inline std::ostream &operator<<(std::ostream &out, const Vec3 &v)
{
    return out << v.e_[0] << ' ' << v.e_[1] << ' ' << v.e_[2];
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.e_[0] + v.e_[0], u.e_[1] + v.e_[1], u.e_[2] + v.e_[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.e_[0] - v.e_[0], u.e_[1] - v.e_[1], u.e_[2] - v.e_[2]);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.e_[0] * v.e_[0], u.e_[1] * v.e_[1], u.e_[2] * v.e_[2]);
}

inline Vec3 operator*(double t, const Vec3 &u)
{
    return Vec3(t * u.e_[0], t * u.e_[1], t * u.e_[2]);
}

inline Vec3 operator*(const Vec3 &u, double t)
{
    return t * u;
}

inline Vec3 operator/(Vec3 v, double t)
{
    return (1 / t) * v;
}

inline double dot(const Vec3 &u, const Vec3 &v)
{
    return u.e_[0] * v.e_[0] + u.e_[1] * v.e_[1] + u.e_[2] * v.e_[2];
}

inline Vec3 cross(const Vec3& u, Vec3& v) {
    return Vec3(
        u.e_[1] * v.e_[2] - u.e_[2] * v.e_[1],
        u.e_[2] * v.e_[0] - u.e_[0] * v.e_[2],
        u.e_[0] * v.e_[1] - u.e_[1] * v.e_[0]
    );
}

inline Vec3 unit_vector(Vec3 v) {
    return v / v.length();
}

Vec3 random_in_unit_sphere() {
    while (true) {
        auto sample = Vec3::random(-1, 1);
        if (sample.length() >= 1) continue;
        return sample;
    }
}

Vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2*dot(v, n)*n;
}