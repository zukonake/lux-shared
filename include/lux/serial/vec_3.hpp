#pragma once 

#include <lux/linear/vec_3.hpp>
#include <lux/serial/serializer.hpp>
#include <lux/serial/deserializer.hpp>
#include <lux/serial/get_size.hpp>

namespace serial
{

template<typename T>
inline SizeT get_size(linear::Vec3<T> const &v)
{
    return get_size(v.x) + get_size(v.y) + get_size(v.z);
}

template<typename T>
inline void clear_buffer(linear::Vec3<T> const &v)
{
    clear_buffer(v.x);
    clear_buffer(v.y);
    clear_buffer(v.z);
}

template<typename T>
inline Serializer &operator<<(Serializer &in, linear::Vec3<T> const &v)
{
    in << v.x;
    in << v.y;
    in << v.z;
    return in;
}

template<typename T>
inline Deserializer &operator>>(Deserializer &out, linear::Vec3<T> &v)
{
    out >> v.x;
    out >> v.y;
    out >> v.z;
    return out;
}

}
