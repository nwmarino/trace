//
//  Hittable.h
//

#pragma once

#include "Ray.h"
#include "Vec.h"

struct HitRecord {
    point3 p = {};
    vec3 normal = {};
    double t = 0.0;
};

class Hittable {
public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const = 0;
};
