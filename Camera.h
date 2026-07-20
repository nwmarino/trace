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
#include "Material.h"

class Camera {
public:
    double aspect_ratio = 1.0;
    double vfov = 90;
    int32_t image_width = 100;
    int32_t samples_per_pixel = 10;
    int32_t max_depth = 10;
    point3 lookFrom = point3(0, 0, 0);
    point3 lookAt = point3(0, 0, -1);
    vec3 vup = vec3(0, 1, 0);

private:
    int32_t image_height = 0;
    double pixel_samples_scale = 0.0;
    point3 center = {};
    point3 px00 = {};
    vec3 pixel_du = {};
    vec3 pixel_dv = {};
    vec3 u = {};
    vec3 v = {};
    vec3 w = {};

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

        center = lookFrom;

        double focal_length = (lookFrom - lookAt).length();
        double theta = toRadians(vfov);
        double h = std::tan(theta / 2);
        double viewport_height = 2.0 * h * focal_length;
        double viewport_width = viewport_height * (double(image_width) / image_height);

        w = unit(lookFrom - lookAt);
        u = unit(cross(vup, w));
        v = cross(w, u);

        vec3 viewport_u = viewport_width * u;
        vec3 viewport_v = viewport_height * -v;

        pixel_du = viewport_u / image_width;
        pixel_dv = viewport_v / image_height;

        vec3 viewport_upper_left = center - (focal_length * w) - viewport_u / 2 - viewport_v / 2;
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
            Ray scattered = {};
            Color attenuation = {};

            if (rec.mat->scatter(r, rec, attenuation, scattered))
                return attenuation * getRayColor(scattered, depth - 1, world);

            return Color(0, 0, 0);
        }

        vec3 unit_dir = unit(r.dir);
        auto a = 0.5 * (unit_dir.y + 1.0);
        return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
    }

    vec3 sampleSquare() const {
        return vec3(randomDouble() - 0.5, randomDouble() - 0.5, 0.0);
    }
};
