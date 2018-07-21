#pragma once

#include <functional>
//
#include <glm/detail/type_vec3.hpp>
//
#include <lux/util/merge_hash.hpp>

namespace linear
{

template<typename T>
using Vec3 = glm::tvec3<T>;

}

namespace std
{

using namespace linear;

template<typename T>
struct hash<Vec3<T>>
{
    size_t operator()(Vec3<T> const &k) const
    {
        return util::merge_hash(hash<T>()(k.x),
                                util::merge_hash(hash<T>()(k.y), hash<T>()(k.z)));
    }
};

}
