#pragma once

#include <lux/linear/vec_2.hpp>
#include <lux/serial/serializer.hpp>
#include <lux/serial/deserializer.hpp>
#include <lux/serial/get_size.hpp>
#include <lux/serial/clear_buffer.hpp>

namespace serial
{

template<typename T>
SizeT get_size(linear::Vec2<T> const &v)
{
    return get_size(v.x) + get_size(v.y);
}

template<typename T>
void clear_buffer(linear::Vec2<T> const &v)
{
    clear_buffer(v.x);
    clear_buffer(v.y);
}

template<typename T>
Serializer &operator<<(Serializer &in, linear::Vec2<T> const &v)
{
    in << v.x;
    in << v.y;
    return in;
}

template<typename T>
Deserializer &operator>>(Deserializer &out, linear::Vec2<T> &v)
{
    out >> v.x;
    out >> v.y;
    return out;
}

}
