#pragma once
#include "ray_tracing_in_one_weekend.h"

class Ray {
    public:
        Ray() {}
        Ray(const Point3& origin, const Vec3& direction) : origin_(origin), direction_(direction) {}

        Point3 origin() const { return origin_; }
        Vec3 direction() const { return direction_; }

        Point3 at(double t) const {
            return origin_ + t*direction_;
        }

    public:
        Point3 origin_;
        Vec3 direction_;

};