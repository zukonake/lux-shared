#pragma once

#include <functional>
//
#include <glm/detail/type_vec3.hpp>
//
#include <util/merge_hash.hpp>
#include <net/serializer.hpp>
#include <net/deserializer.hpp>

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

namespace net
{

using namespace linear;

template<typename T>
inline Serializer &operator<<(Serializer &in, Vec3<T> const &v)
{
    in << v.x;
    in << v.y;
    in << v.z;
    return in;
}

template<typename T>
inline Deserializer &operator>>(Deserializer &out, Vec3<T> &v)
{
    out >> v.x;
    out >> v.y;
    out >> v.z;
    return out;
}

}
