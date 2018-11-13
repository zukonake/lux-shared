#pragma once

#include <cfloat>
#include <cstdlib>
//
#include <lux_shared/int.hpp>

inline bool f32_cmp(F32 a, F32 b) {
    //@TODO?
    return std::abs(a - b) < FLT_EPSILON;
}

F32 constexpr tau = 6.28318530717958647692528676655900576839433879875021;
