#pragma once

#include <functional>
//
#include <glm/detail/type_vec2.hpp>
//
#include <lux/alias/scalar.hpp>
#include <lux/util/merge_hash.hpp>

template<typename T>
using Vec2 = glm::tvec2<T>;

namespace std
{

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
