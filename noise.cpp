#include <SimplexNoise/SimplexNoise.hpp>
//
#include <lux_shared/noise.hpp>

//@TODO add random seed

F32 noise(F32 seed) {
    return SimplexNoise::noise(seed);
}

F32 noise(Vec2F seed) {
    return SimplexNoise::noise(seed.x, seed.y);
}

F32 noise(Vec3F seed) {
    return SimplexNoise::noise(seed.x, seed.y, seed.z);
}

template<typename T>
F32 noise_fbm(T seed, Uns octaves)
{
    F32 sum = 0.f;
    F32 amp = 0.5f;
    for(Uns i = 0; i < octaves; ++i) {
        sum  += noise(seed) * amp;
        ///we don't multiply exactly by 2, because that makes the octaves
        ///overlap
        seed *= 1.9f;
        amp  *= 0.5f;
    }
    return sum / (1.f - 2.f * amp);
}

template F32 noise_fbm<F32>(  F32   seed, Uns octaves);
template F32 noise_fbm<Vec2F>(Vec2F seed, Uns octaves);
template F32 noise_fbm<Vec3F>(Vec3F seed, Uns octaves);
