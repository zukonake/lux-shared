#pragma once

#include <lux_shared/int.hpp>
#include <lux_shared/vec.hpp>

F32 noise(F32 seed);
F32 noise(Vec2F seed);
F32 noise(Vec3F seed);

template<typename T>
F32 noise_fbm(T seed, Uns octaves);
