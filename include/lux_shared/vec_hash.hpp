#pragma once

#include <functional>
//
#include <lux_shared/int.hpp>
#include <lux_shared/util/merge_hash.hpp>
#include <lux_shared/vec.hpp>

template<typename T>
struct std::hash<Vec2<T>>
{
    SizeT operator()(Vec2<T> const &k) const
    {
        return util::merge_hash(std::hash<T>()(k.x),
                                std::hash<T>()(k.y));
    }
};

template<typename T>
struct std::hash<Vec3<T>>
{
    SizeT operator()(Vec3<T> const &k) const
    {
        return util::merge_hash(std::hash<T>()(k.x),
               util::merge_hash(std::hash<T>()(k.y),
                                std::hash<T>()(k.z)));
    }
};

template<typename T>
struct std::hash<Vec4<T>>
{
    SizeT operator()(Vec4<T> const &k) const
    {
        return util::merge_hash(std::hash<T>()(k.x),
               util::merge_hash(std::hash<T>()(k.y),
               util::merge_hash(std::hash<T>()(k.z),
                                std::hash<T>()(k.w))));
    }
};
