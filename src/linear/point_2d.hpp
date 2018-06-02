#pragma once

#include <functional>
//
#include <glm/detail/type_vec2.hpp>
//
#include <util/merge_hash.hpp>

namespace linear
{

template<typename T>
using Point2d = glm::tvec2<T>;

}

namespace std
{

using namespace linear;

template<typename T>
struct hash<Point2d<T>>
{
    size_t operator()(Point2d<T> const &k) const
    {
        return util::merge_hash(hash<T>()(k.x), hash<T>()(k.y));
    }
};

}
