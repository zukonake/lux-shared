#pragma once

#include <functional>
//
#include <glm/detail/type_vec3.hpp>
//
#include <lux/alias/scalar.hpp>
#include <lux/util/merge_hash.hpp>

template<typename T>
using Vec3 = glm::tvec3<T>;

namespace std
{

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

class Serializer;
class Deserializer;

template<typename T>
SizeT get_size(Vec3<T> const &v);
template<typename T>
void clear_buffer(Vec3<T> const &v);
template<typename T>
Serializer &operator<<(Serializer &in, Vec3<T> const &v);
template<typename T>
Deserializer &operator>>(Deserializer &out, Vec3<T> &v);

}
