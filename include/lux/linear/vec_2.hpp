#pragma once

#include <functional>
//
#include <glm/detail/type_vec2.hpp>
//
#include <lux/alias/scalar.hpp>
#include <lux/util/merge_hash.hpp>

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

namespace serial
{

class Serializer;
class Deserializer;

template<typename T>
SizeT get_size(linear::Vec2<T> const &v);

template<typename T>
void clear_buffer(linear::Vec2<T> const &v);

template<typename T>
Serializer &operator<<(Serializer &in, linear::Vec2<T> const &v);

template<typename T>
Deserializer &operator>>(Deserializer &out, linear::Vec2<T> &v);

}
