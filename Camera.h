//
//  Camera.h
//

#pragma once

#include "Hittable.h"
#include "Ray.h"
#include "Shared.h"
#include "Vec.h"
#include "Interval.h"
#include "Writer.h"

class Camera {
public:
    double aspect_ratio = 1.0;
    int32_t image_width = 100;
    int32_t samples_per_pixel = 10;
    int32_t max_depth = 10;

private:
    int32_t image_height = 0;
    double pixel_samples_scale = 0.0;
    point3 center = {};
    point3 px00 = {};
    vec3 pixel_du = {};
    vec3 pixel_dv = {};

public:
    void render(const Hittable& world) {
        init();

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int32_t j = 0; j < image_height; ++j) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;

            for (int32_t i = 0; i < image_width; ++i) {
                Color color(0, 0, 0);

                for (int32_t sample = 0; sample < samples_per_pixel; ++sample) {
                    Ray r = getRay(i, j);
                    color += getRayColor(r, max_depth, world);
                }

                writeColor(std::cout, pixel_samples_scale * color);
            }
        }

        std::clog << "\rDone.                 \n";
    }

private:
    void init() {
        image_height = std::max(1, int32_t(image_width / aspect_ratio));
        center = point3(0, 0, 0);

        pixel_samples_scale = 1.0 / samples_per_pixel;

        double focal_length = 1.0;
        double viewport_height = 2.0;
        double viewport_width = viewport_height * (double(image_width) / image_height);

        vec3 viewport_u = vec3(viewport_width, 0, 0);
        vec3 viewport_v = vec3(0, -viewport_height, 0);

        pixel_du = viewport_u / image_width;
        pixel_dv = viewport_v / image_height;

        vec3 viewport_upper_left = center - vec3(0, 0, focal_length) - (viewport_u / 2) - (viewport_v / 2);
        px00 = viewport_upper_left + 0.5 * (pixel_du + pixel_dv);
    }

    Ray getRay(int32_t i, int32_t j) const {
        vec3 offset = sampleSquare();
        vec3 sample = px00 + ((i + offset.x) * pixel_du) + ((j + offset.y) * pixel_dv);

        return Ray(center, sample - center);
    }

    Color getRayColor(const Ray& r, int32_t depth, const Hittable& world) const {
        if (depth <= 0)
            return Color(0, 0, 0);
        
        HitRecord rec = {};

        if (world.hit(r, Interval(0.001, +inf), rec)) {
            vec3 dir = rec.normal + randomUnit();
            return 0.5 * getRayColor(Ray(rec.p, dir), depth - 1, world);
        }

        vec3 unit_dir = unit(r.dir);
        auto a = 0.5 * (unit_dir.y + 1.0);
        return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
    }

    vec3 sampleSquare() const {
        return vec3(randomDouble() - 0.5, randomDouble() - 0.5, 0.0);
    }
};
