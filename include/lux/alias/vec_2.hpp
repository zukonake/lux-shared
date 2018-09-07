#pragma once

#include <functional>
//
#include <glm/detail/type_vec2.hpp>
//
#include <lux/alias/scalar.hpp>
#include <lux/util/merge_hash.hpp>
#include <lux/util/packer.hpp>

template<typename T>
using Vec2 = glm::tvec2<T>;

typedef Vec2<U16> Vec2US;
typedef Vec2<U32> Vec2UI;
typedef Vec2<I16> Vec2S;
typedef Vec2<I32> Vec2I;
typedef Vec2<I64> Vec2L;
typedef Vec2<F32> Vec2F;
typedef Vec2<F64> Vec2D;

template<typename T>
struct std::hash<Vec2<T>>
{
    SizeT operator()(Vec2<T> const &k) const
    {
        return util::merge_hash(std::hash<T>()(k.x), std::hash<T>()(k.y));
    }
};

template<typename T>
struct util::Packer<Vec2<T>>
{
    SizeT operator()(Vec2<T> const &k) const
    {
        return (*(SizeT const *)&k.y << 32) |
               (*(SizeT const *)&k.x & 0xFFFF'FFFF);
    }
};

namespace net
{

class Serializer;
class Deserializer;

template<typename T>
SizeT get_size(Vec2<T> const &v);
template<typename T>
void clear_buffer(Vec2<T> const &v);
template<typename T>
Serializer &operator<<(Serializer &in, Vec2<T> const &v);
template<typename T>
Deserializer &operator>>(Deserializer &out, Vec2<T> &v);

}
