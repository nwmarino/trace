//
//  Shared.h
//

#pragma once

#include <cmath>
#include <limits>

constexpr double INF = std::numeric_limits<double>::infinity();
constexpr double PI = 3.1415926535897932385;

inline double toRadians(double deg) {
    return (deg * PI) / 180.0;
}
