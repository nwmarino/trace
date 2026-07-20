//
//  ray.h
//

#pragma once

#include "Vec.h"

struct Ray {
    point3 origin = {};
    vec3 dir = {};

    Ray() = default;
    
    Ray(const point3& origin, const vec3& dir)
        : origin(origin)
        , dir(dir) {}

    point3 at(double t) const {
        return origin + (t * dir);
    }
};
