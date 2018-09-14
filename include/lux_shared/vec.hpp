#pragma once

#include <glm/detail/type_vec.hpp>
//
#include <lux_shared/int.hpp>

template<SizeT dim, typename T>
using Vec = glm::vec<dim, T, glm::defaultp>;

template<typename T>
using Vec2 = Vec<2, T>;
template<typename T>
using Vec3 = Vec<3, T>;
template<typename T>
using Vec4 = Vec<4, T>;

typedef Vec<2, F32> Vec2F;
typedef Vec<2, F64> Vec2D;
typedef Vec<2, Int> Vec2I;
typedef Vec<2, Uns> Vec2U;

typedef Vec<3, F32> Vec3F;
typedef Vec<3, F64> Vec3D;
typedef Vec<3, Int> Vec3I;
typedef Vec<3, Uns> Vec3U;

typedef Vec<4, F32> Vec4F;
typedef Vec<4, F64> Vec4D;
typedef Vec<4, Int> Vec4I;
typedef Vec<4, Uns> Vec4U;

