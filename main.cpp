#include <iostream>
#include "ray_tracing_in_one_weekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "camera.h"
#include "color.h"


Color ray_color(const Ray& r, const Hittable& world, int depth) {
    HitRecord rec;

    if (depth <= 0) {
        return Color(0, 0, 0);
    }

    if (world.hit(r, 0.001, infinity, rec)) {
        Ray scattered;
        Color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, depth-1);
        }
        return Color(0.0, 0.0, 0.0);
    }

    Vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*Color(1.0, 1.0, 1.0) +t*Color(0.5, 0.7, 1.0);
}

int main() {   
    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 50;
    const int max_depth = 5;
    
    // World

    HittableList world;

    auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
    auto material_left   = std::make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);
    auto material_right  = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    world.add(std::make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, material_right));
    world.add(std::make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(std::make_shared<Sphere>(Point3( 0.0,    0.0, -1.0),   0.5, material_center));

    // Camera
    Camera camera(aspect_ratio, 2.0, 1.0);

    // Render
    std::cout << "P3" << std::endl << image_width << " " << image_height << std::endl << "255" << std::endl;

    for (int j = image_height-1; j >=0; j--) {
        std::cerr << "\rScan lines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            Color pixel_color(0, 0, 0);
            for (int sample=0; sample < samples_per_pixel; sample++) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                Ray r = camera.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
}