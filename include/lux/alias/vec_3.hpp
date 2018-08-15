#pragma once

#include <functional>
//
#include <glm/detail/type_vec3.hpp>
//
#include <lux/alias/scalar.hpp>

template<typename T>
using Vec3 = glm::tvec3<T>;

namespace std
{

template<typename T>
struct hash<Vec3<T>>
{
    size_t operator()(Vec3<T> const &k) const
    {
        return  ((size_t)k.z            << 40) |
               (((size_t)k.y & 0xFFFFF) << 20) |
                ((size_t)k.x & 0xFFFFF);
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
