//
//  Shared.h
//

#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <random>

struct vec3;

using Color = vec3;

constexpr double inf = std::numeric_limits<double>::infinity();
constexpr double PI = 3.1415926535897932385;

inline double toRadians(double deg) {
    return (deg * PI) / 180.0;
}

inline double randomDouble() {
    return std::rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max) {
    return min + (max - min) * randomDouble();
}

inline double linearToGamma(double linear) {
    if (linear > 0)
        return std::sqrt(linear);

    return 0;
}
