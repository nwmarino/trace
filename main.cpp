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

    auto mat_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto mat_center = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto mat_left = std::make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);
    auto mat_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    world.add(std::make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100.0, mat_ground));
    world.add(std::make_shared<Sphere>(point3(0.0,    0.0, -1.2), 0.5, mat_center));
    world.add(std::make_shared<Sphere>(point3(-1.0, 0.0, -1.0), 0.5, mat_left));
    world.add(std::make_shared<Sphere>(point3(1.0, 0.0, -1.0), 0.5, mat_right));

    Camera camera = {};

    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 720;
    camera.samples_per_pixel = 16;
    camera.max_depth = 16;

    camera.render(world);
}
