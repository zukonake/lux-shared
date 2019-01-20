#pragma once

#include <cfloat>
#include <cstdlib>
//
#include <glm/glm.hpp>
#include <lux_shared/int.hpp>

inline F32 p_norm(F32 a) {
    return (a + 1.f) / 2.f;
}

inline F32 n_norm(F32 a) {
    return (a - 0.5f) * 2.f;
}

template<typename T>
inline T rcp(T a) {
    return (T)1 / a;
}

using glm::clamp;
using glm::pow;
using glm::sqrt;
using glm::min;
using glm::max;
using glm::fract;
using glm::floor;
using glm::ceil;
using glm::round;
using glm::abs;
using glm::normalize;
using glm::dot;
using glm::cross;
using glm::length;
using glm::distance;
using glm::sin;
using glm::cos;

inline bool f32_cmp(F32 a, F32 b, F32 diff) {
    return abs(a - b) < diff;
}

F32 constexpr tau = 6.28318530717958647692528676655900576839433879875021f;
