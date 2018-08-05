#pragma once

#include <lux/alias/vec_2.hpp>
#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>
#include <lux/net/get_size.hpp>
#include <lux/net/clear_buffer.hpp>

namespace net
{

template<typename T>
SizeT get_size(Vec2<T> const &v)
{
    return get_size(v.x) + get_size(v.y);
}

template<typename T>
void clear_buffer(Vec2<T> const &v)
{
    clear_buffer(v.x);
    clear_buffer(v.y);
}

template<typename T>
Serializer &operator<<(Serializer &in, Vec2<T> const &v)
{
    in << v.x;
    in << v.y;
    return in;
}

template<typename T>
Deserializer &operator>>(Deserializer &out, Vec2<T> &v)
{
    out >> v.x;
    out >> v.y;
    return out;
}

}
