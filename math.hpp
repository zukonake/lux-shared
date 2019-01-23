#pragma once

#include <cfloat>
#include <cstdlib>
//
#include <glm/glm.hpp>
#include <lux_shared/int.hpp>

using glm::clamp;
using glm::sign;
using glm::pow;
using glm::sqrt;
using glm::min;
using glm::max;
using glm::fract;
using glm::floor;
using glm::ceil;
using glm::round;
using glm::trunc;
using glm::abs;
using glm::normalize;
using glm::dot;
using glm::cross;
using glm::length;
using glm::distance;
using glm::sin;
using glm::cos;
using glm::mix;
using glm::mod;
using glm::modf;

inline F32 u_norm(F32 const& a) {
    return (a + 1.f) / 2.f;
}

inline F32 s_norm(F32 const& a) {
    return (a - 0.5f) * 2.f;
}

template<typename T>
inline T rcp(T const& a) {
    return T(1) / a;
}

template<typename T>
inline T s_mod_clamp(T a, T const& bound) {
    if(a <= -bound) {
        return bound - (1.f - fract(a / bound)) * bound;
    } else if(a > bound) {
        return -bound + fract(a / bound) * bound;
    } else return a;
}

template<typename T>
inline T mod_clamp(T a, T const& bound) {
    if(a > bound) {
        return fract(a / bound) * bound;
    } else return a;
}

template<typename T>
inline bool diff_cmp(T const& a, T const& b, T const& diff) {
    return abs(a - b) < diff;
}

F32 constexpr tau = 6.28318530717958647692528676655900576839433879875021f;
