#pragma once

#include <lux/alias/vec_3.hpp>
#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>
#include <lux/net/get_size.hpp>
#include <lux/net/clear_buffer.hpp>

namespace net
{

template<typename T>
SizeT get_size(Vec3<T> const &v)
{
    return get_size(v.x) + get_size(v.y) + get_size(v.z);
}

template<typename T>
void clear_buffer(Vec3<T> const &v)
{
    clear_buffer(v.x);
    clear_buffer(v.y);
    clear_buffer(v.z);
}

template<typename T>
Serializer &operator<<(Serializer &in, Vec3<T> const &v)
{
    in << v.x;
    in << v.y;
    in << v.z;
    return in;
}

template<typename T>
Deserializer &operator>>(Deserializer &out, Vec3<T> &v)
{
    out >> v.x;
    out >> v.y;
    out >> v.z;
    return out;
}

}
