#pragma once

#include "ray_tracing_in_one_weekend.h"

class Camera {
    public:
        Camera(double aspect_ratio, double viewport_height, double focal_length) {
            auto viewport_width = aspect_ratio * viewport_height;

            origin_ = Point3(0, 0, 0);
            horizontal_ = Vec3(viewport_width, 0, 0);
            vertical_ = Vec3(0, viewport_height, 0);
            lower_left_corner_ = origin_ - horizontal_/2 - vertical_/2 - Vec3(0, 0, focal_length);
        }

        Ray get_ray(double u, double v) {
            // starting at origin
            // going from origin to viewport @ (u, v)
            return Ray(origin_, lower_left_corner_ + u*horizontal_ + v*vertical_ - origin_);
        }

    private:
        Point3 origin_;
        Point3 lower_left_corner_;
        Vec3 horizontal_;
        Vec3 vertical_;

};