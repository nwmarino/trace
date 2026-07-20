//
//  Writer.h
//

#pragma once

#include "Interval.h"
#include "Shared.h"
#include "Vec.h"

#include <iostream>

inline void writeColor(std::ostream& out, const Color& px) {
    static const Interval intensity(0.000, 0.999);

    int32_t r_byte = int32_t(256 * intensity.clamp(linearToGamma(px.r)));
    int32_t g_byte = int32_t(256 * intensity.clamp(linearToGamma(px.g)));
    int32_t b_byte = int32_t(256 * intensity.clamp(linearToGamma(px.b)));

    out << r_byte << ' ' << g_byte << ' ' << b_byte << '\n';
}
