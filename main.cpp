//
//  main.cpp
//

#include "Ray.h"
#include "Vec.h"
#include "Hittable.h"
#include "Sphere.h"
#include "Shared.h"

#include <iostream>

using color = vec3;

void writeColor(std::ostream& out, const color& px) {
    int32_t r_byte = int32_t(255.999 * px.r);
    int32_t g_byte = int32_t(255.999 * px.g);
    int32_t b_byte = int32_t(255.999 * px.b);

    out << r_byte << ' ' << g_byte << ' ' << b_byte << '\n';
}

color ray_color(const Ray& r, const Hittable& world) {
    HitRecord rec = {};
    if (world.hit(r, 0, INF, rec))
        return 0.5 * (rec.normal + color(1, 1, 1));
    
    vec3 unit_dir = unit(r.dir);
    auto a = 0.5 * (unit_dir.y + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int32_t main() {
    double aspect = 16.0 / 9.0;
    int32_t width = 720u;
    int32_t height = std::max(1, int32_t(width / aspect));

    HittableList world = {};
    world.add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(point3(0, -100.5, -1), 100));

    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (double(width) / height);
    point3 camera_center = point3(0, 0, 0);

    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    vec3 pixel_du = viewport_u / width;
    vec3 pixel_dv = viewport_v / height;

    vec3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - (viewport_u / 2) - (viewport_v / 2);
    vec3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_du + pixel_dv);

    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    for (int32_t j = 0; j < height; ++j) {
        std::clog << "\rScanlines remaining: " << (height - j) << ' ' << std::flush;

        for (int32_t i = 0; i < width; ++i) {
            auto pixel_center = pixel00_loc + (i * pixel_du) + (j * pixel_dv);
            auto ray_dir = pixel_center - camera_center;
            Ray r(camera_center, ray_dir);

            color pixel_color = ray_color(r, world);
            writeColor(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}
