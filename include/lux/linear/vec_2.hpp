#pragma once

#include <functional>
//
#include <glm/detail/type_vec2.hpp>
//
#include <lux/util/merge_hash.hpp>
#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>

namespace linear
{

template<typename T>
using Vec2 = glm::tvec2<T>;

}

namespace std
{

using namespace linear;

template<typename T>
struct hash<Vec2<T>>
{
    size_t operator()(Vec2<T> const &k) const
    {
        return util::merge_hash(hash<T>()(k.x), hash<T>()(k.y));
    }
};

}

namespace net
{

using namespace linear;

template<typename T>
inline Serializer &operator<<(Serializer &in, Vec2<T> const &v)
{
    in << v.x;
    in << v.y;
    return in;
}

template<typename T>
inline Deserializer &operator>>(Deserializer &out, Vec2<T> &v)
{
    out >> v.x;
    out >> v.y;
    return out;
}

}
