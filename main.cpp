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

    auto R = std::cos(PI / 4);

    auto mat_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto mat_center = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto mat_left = std::make_shared<Dialectric>(1.50);
    auto mat_bubble = std::make_shared<Dialectric>(1.00 / 1.50);
    auto mat_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    world.add(std::make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100.0, mat_ground));
    world.add(std::make_shared<Sphere>(point3(0.0,    0.0, -1.2), 0.5, mat_center));
    world.add(std::make_shared<Sphere>(point3(-1.0, 0.0, -1.0), 0.5, mat_left));
    world.add(std::make_shared<Sphere>(point3(-1.0, 0.0, -1.0), 0.4, mat_bubble));
    world.add(std::make_shared<Sphere>(point3(1.0, 0.0, -1.0), 0.5, mat_right));

    Camera camera = {};

    camera.aspect_ratio = 16.0 / 9.0;
    camera.vfov = 90;
    camera.image_width = 720;
    camera.samples_per_pixel = 10;
    camera.max_depth = 16;
    camera.lookFrom = point3(-2, 2, 1);
    camera.lookAt = point3(0, 0, -1);
    camera.vup = vec3(0, 1, 0);

    camera.render(world);
}
