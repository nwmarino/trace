//
//  Sphere.h
//

#pragma once

#include "Hittable.h"

class Sphere : public Hittable {
    point3 center = {};
    double radius = {};
    std::shared_ptr<Material> mat = nullptr;

public:
    Sphere(const point3& center, double radius, std::shared_ptr<Material> mat) 
        : center(center)
        , radius(std::fmax(0, radius))
        , mat(mat) {}

    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override {
        vec3 oc = center - r.origin;
        double a = r.dir.length_squared();
        double h = dot(r.dir, oc);
        double c = oc.length_squared() - (radius * radius);

        double discriminant = (h * h) - (a * c);
        if (discriminant < 0)
            return false;

        double sqrtd = std::sqrt(discriminant);
        double root = (h - sqrtd) / a;

        if (!ray_t.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        rec.setFaceNormal(r, (rec.p - center) / radius);
        rec.mat = mat;
        return true;
    }
};
