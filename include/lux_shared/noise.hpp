#pragma once

#include <simplex/SimplexNoise.h>
#include <lux_shared/int.hpp>

F32 noise(F32 const& seed) {
    return SimplexNoise::noise(seed);
}

F32 noise(Vec2F const& seed) {
    return SimplexNoise::noise(seed.x, seed.y);
}

F32 noise(Vec3F const& seed) {
    return SimplexNoise::noise(seed.x, seed.y, seed.z);
}

template<typename T>
F32 noise_fbm(T seed, Uns octaves) {
    F32 sum = 0.f;
    F32 amp = 0.5f;
    for(Uns i = 0; i < octaves; ++i) {
        sum  += noise(seed) * amp;
        seed *= 2.f;
        amp  *= 0.5f;
    }
    return sum / (1.f - 2.f * amp);
}
