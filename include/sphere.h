#pragma once

#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable {
    public:
        Sphere() {}
        Sphere(Point3 center, double radius) : center_(center), radius_(radius) {};

        virtual bool hit(
            const Ray& r, double t_min, double t_max, HitRecord& rec
        ) const override;

    public:
        Point3 center_;
        double radius_;
};

bool Sphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    // Does somewhere on the ray P(t) hit the circle?
    // In other words, does there exist a point on the ray such that
    // the vector from the center of the circle to that ray
    // is the radius?
    // |(P(t) - C)| = r
    // |(A + tb - C)| = r
    // (A + tb - C) . (A + tb - C) = r^2
    // Expanding this out
    // A.A + A.tb + A.-C + tb.A + tb.tb + tb.-C + -C.A + -C.tb + -C.-C = r*r
    // Collecting like terms
    // A.A + 2A.tb + 2A.-C + t*tb.b + 2tb.-C + -C.-C = r*r
    // rearranging so it looks like a quadratic
    // note A.A + -C.-C is equal to (A-C).(A-C)
    // Collect t^2
    // t^2 b.b
    // Collect t^1
    // 2A.tb + 2tb.-C or 2tb.(A-C)
    // Collect t^0
    // A.A + 2A.-C + -C.-C - r^2
    // note that in general (a-b)^2 = a^2 - 2ab +c^2 so...
    // A.A + 2A.-C + -C.-C - r^2 = (A-C).(A-C) - r^2
    // Now rewriting in quadratic form
    // t^2 (b.b) + t (2b.(A-C)) + [(A-C).(A-C)-r^2]
    // we can now use the quadratic formula to solve for t
    // if the discriminant is greater than 0 then there is a solution

    Vec3 q = r.origin() - center_;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(q, r.direction());
    auto c = dot(q, q) - radius_*radius_;
    auto discriminant = b*b - 4*a*c;
    if (discriminant < 0)
        return false;

    auto sqrtd = sqrt(discriminant);

    // find the nearest root within t_min t_max
    auto root = (-b - sqrtd) / (2.0*a);
    if (root < t_min || root > t_max) {
        root = (-b + sqrtd) / (2.0*a);
        if (root < t_min || root > t_max)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    Vec3 outward_normal = (rec.p - center_) / radius_;
    rec.set_face_normal(r, outward_normal);
    return true;
}

