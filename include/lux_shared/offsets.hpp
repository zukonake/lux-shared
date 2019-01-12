#pragma once

#include <lux_shared/vec.hpp>

///clockwise order of vertices
template<typename T>
Vec2<T> constexpr quad[] =
    {{-1, -1}, { 1, -1},
     { 1,  1}, {-1,  1}};

template<typename T>
Vec2<T> constexpr u_quad[] =
    {{0, 0}, {1, 0},
     {1, 1}, {0, 1}};

template<typename T>
T constexpr quad_idxs[] = {0, 1, 2, 2, 3, 0};

template<typename T>
Vec2<T> constexpr manhattan_2d[] =
             {{0, -1},
     {-1, 0}, {0,  0}, {1, 0},
              {0,  1}};

template<typename T>
Vec3<T> constexpr manhattan[] =
    {{0, -1, 0}, {-1, 0, 0}, {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, -1},
     {0, 0, 1}};

template<typename T>
Vec2<T> constexpr manhattan_hollow_2d[] =
    {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

template<typename T>
Vec3<T> constexpr manhattan_hollow[] =
    {{0, -1, 0}, {-1, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1}};

template<typename T>
Vec2<T> constexpr chebyshev_2d[] =
    {{-1, -1}, { 0, -1}, { 1, -1},
     {-1,  0}, { 0,  0}, { 1,  0},
     {-1,  1}, { 0,  1}, { 1,  1}};

template<typename T>
Vec2<T> constexpr chebyshev_hollow_2d[] =
    {{-1, -1}, { 0, -1}, { 1, -1},
     {-1,  0}          , { 1,  0},
     {-1,  1}, { 0,  1}, { 1,  1}};

template<typename T>
Vec3<T> constexpr chebyshev[] =
    {{-1, -1, -1}, { 0, -1, -1}, { 1, -1, -1},
     {-1,  0, -1}, { 0,  0, -1}, { 1,  0, -1},
     {-1,  1, -1}, { 0,  1, -1}, { 1,  1, -1},
     {-1, -1,  0}, { 0, -1,  0}, { 1, -1,  0},
     {-1,  0,  0}, { 0,  0,  0}, { 1,  0,  0},
     {-1,  1,  0}, { 0,  1,  0}, { 1,  1,  0},
     {-1, -1,  1}, { 0, -1,  1}, { 1, -1,  1},
     {-1,  0,  1}, { 0,  0,  1}, { 1,  0,  1},
     {-1,  1,  1}, { 0,  1,  1}, { 1,  1,  1}};

template<typename T>
Vec2<T> constexpr chebyshev_hollow[] =
    {{-1, -1, -1}, { 0, -1, -1}, { 1, -1, -1},
     {-1,  0, -1}, { 0,  0, -1}, { 1,  0, -1},
     {-1,  1, -1}, { 0,  1, -1}, { 1,  1, -1},
     {-1, -1,  0}, { 0, -1,  0}, { 1, -1,  0},
     {-1,  0,  0},               { 1,  0,  0},
     {-1,  1,  0}, { 0,  1,  0}, { 1,  1,  0},
     {-1, -1,  1}, { 0, -1,  1}, { 1, -1,  1},
     {-1,  0,  1}, { 0,  0,  1}, { 1,  0,  1},
     {-1,  1,  1}, { 0,  1,  1}, { 1,  1,  1}};
