#pragma once

#include <functional>
//
#include <glm/detail/type_vec3.hpp>
//
#include <lux/alias/scalar.hpp>
#include <lux/util/merge_hash.hpp>
#include <lux/util/packer.hpp>

template<typename T>
using Vec3 = glm::tvec3<T>;

template<typename T>
struct std::hash<Vec3<T>>
{
    SizeT operator()(Vec3<T> const &k) const
    {
        return util::merge_hash(std::hash<T>()(k.x),
               util::merge_hash(std::hash<T>()(k.y), std::hash<T>()(k.z)));
    }
};

template<typename T>
struct util::Packer<Vec3<T>>
{
    SizeT operator()(Vec3<T> const &k) const
    {
        return  ((SizeT)k.z            << 40) |
               (((SizeT)k.y & 0xFFFFF) << 20) |
                ((SizeT)k.x & 0xFFFFF);
    }
};

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
