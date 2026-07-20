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
    world.add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(point3(0, -100.5, -1), 100));

    Camera camera = {};

    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 720;
    camera.samples_per_pixel = 16;
    camera.max_depth = 16;

    camera.render(world);
}
