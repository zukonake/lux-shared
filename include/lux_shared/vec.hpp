#pragma once

///for those constexpr ctors
#define GLM_FORCE_PURE
#include <glm/glm.hpp>
#include <glm/detail/qualifier.hpp>
//
#include <lux_shared/int.hpp>

template<typename T, SizeT DIM>
using Vec = glm::vec<DIM, T, glm::defaultp>;

template<typename T>
using Vec2 = Vec<T, 2>;
template<typename T>
using Vec3 = Vec<T, 3>;
template<typename T>
using Vec4 = Vec<T, 4>;

typedef Vec2<F32> Vec2F;
typedef Vec2<F64> Vec2D;
typedef Vec2<Int> Vec2I;
typedef Vec2<Uns> Vec2U;

typedef Vec3<F32> Vec3F;
typedef Vec3<F64> Vec3D;
typedef Vec3<Int> Vec3I;
typedef Vec3<Uns> Vec3U;

typedef Vec4<F32> Vec4F;
typedef Vec4<F64> Vec4D;
typedef Vec4<Int> Vec4I;
typedef Vec4<Uns> Vec4U;
