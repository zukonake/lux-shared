#pragma once

#include <functional>
//
#include <glm/detail/type_vec3.hpp>
//
#include <util/merge_hash.hpp>

namespace linear
{

template<typename T>
using Point3d = glm::tvec3<T>;

}

namespace std
{

using namespace linear;

template<typename T>
struct hash<Point3d<T>>
{
    size_t operator()(Point3d<T> const &k) const
    {
        return util::merge_hash(hash<T>()(k.x),
                                util::merge_hash(hash<T>()(k.y), hash<T>()(k.z)));
    }
};

}
