#pragma once

#include <functional>
//
#include <glm/detail/type_vec3.hpp>
//
#include <lux/alias/scalar.hpp>
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

namespace serial
{

class Serializer;
class Deserializer;

template<typename T>
SizeT get_size(linear::Vec3<T> const &v);

template<typename T>
void clear_buffer(linear::Vec3<T> const &v);

template<typename T>
Serializer &operator<<(Serializer &in, linear::Vec3<T> const &v);

template<typename T>
Deserializer &operator>>(Deserializer &out, linear::Vec3<T> &v);

}
