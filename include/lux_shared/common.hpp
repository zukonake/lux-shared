#pragma once

#include <cmath>
#include <cfloat>
//
#include <lux_shared/int.hpp>
#include <lux_shared/macro.hpp>
#include <lux_shared/memory.hpp>
#include <lux_shared/vec.hpp>
#include <lux_shared/containers.hpp>
#include <lux_shared/random.hpp>

inline bool f32_cmp(F32 a, F32 b) {
    return std::fabs(a - b) < FLT_EPSILON;
}
