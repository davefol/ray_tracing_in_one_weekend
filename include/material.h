#pragma once

struct HitRecord;

#include "ray_tracing_in_one_weekend.h"


class Material {
    public:
        virtual bool scatter(
            const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
        ) const = 0;
};

class Lambertian : public Material {
    public:
        Lambertian(Color albedo) : albedo_(albedo) {}

        virtual bool scatter(
            const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
        ) const override {
            auto scatter_direction = rec.normal + random_unit_vector();
            if (scatter_direction.near_zero()) {
                scatter_direction = rec.normal;
            }
            scattered = Ray(rec.p, scatter_direction);
            attenuation = albedo_;
            return true;
        }

    public:
        Color albedo_;
};

class Metal : public Material {
    public:
        Metal(Color albedo, double fuzz) : albedo_(albedo), fuzz_(fuzz) {}

        virtual bool scatter(
            const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
        ) const override {
            Vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = Ray(rec.p, reflected + fuzz_ * random_in_unit_sphere());
            attenuation = albedo_;
            return dot(scattered.direction(), rec.normal) > 0;
        }

    public:
        Color albedo_;
        double fuzz_;
};