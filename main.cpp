//
//  main.cpp
//

#include "Camera.h"
#include "Hittable.h"
#include "Interval.h"
#include "Sphere.h"
#include "Shared.h"

#include <iostream>

int32_t main() {
    HittableList world = {};

    auto ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(point3(0, -1000, 0), 1000, ground_material));

    for (int32_t a = -11; a < 11; ++a) {
        for (int32_t b = -11; b < 11; ++b) {
            auto choose_mat = randomDouble();
            point3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material = nullptr;

                if (choose_mat < 0.8) {
                    auto albedo = Color::random() * Color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = randomDouble(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    sphere_material = std::make_shared<Dialectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto mat1 = std::make_shared<Dialectric>(1.5);
    world.add(std::make_shared<Sphere>(point3(0, 1, 0), 1.0, mat1));

    auto mat2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(point3(-4, 1, 0), 1.0, mat2));

    auto mat3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(point3(4, 1, 0), 1.0, mat3));

    Camera camera = {};

    camera.aspect_ratio = 16.0 / 9.0;
    camera.vfov = 20;
    camera.image_width = 1080;
    camera.samples_per_pixel = 128;
    camera.max_depth = 50;
    camera.lookFrom = point3(13, 2, 3);
    camera.lookAt = point3(0, 0, 0);
    camera.vup = vec3(0, 1, 0);
    camera.defocus_angle = 0.6;
    camera.focus_dist = 10.0;

    camera.render(world);
}
