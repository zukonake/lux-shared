#pragma once

#include <cassert>
//
#include <lux/alias/scalar.hpp>
#include <lux/alias/array.hpp>
#include <lux/serial/serializer.hpp>
#include <lux/serial/deserializer.hpp>
#include <lux/serial/get_size.hpp>
#include <lux/serial/clear_buffer.hpp>

namespace serial
{

template<typename T, SizeT len>
inline SizeT get_size(Array<T, len> const &v)
{
    if constexpr(std::is_trivial<T>::value)
    {
        return sizeof(T) * len;
    }
    else
    {
        SizeT size = 0;
        for(auto const &i : v) size += get_size(i);
        return size;
    }
}

template<typename T, SizeT len>
inline void clear_buffer(Array<T, len> &v)
{
    if constexpr(std::is_trivial<T>::value == false)
    {
        for(auto const &i : v) clear_buffer(i);
    }
}

template<typename T, SizeT len>
inline Serializer &operator<<(Serializer &in, Array<T, len> const &v)
{
    for(SizeT i = 0; i < len; ++i) in << v[i];
    return in;
}

template<typename T, SizeT len>
inline Deserializer &operator>>(Deserializer &out, Array<T, len> &v)
{
    for(SizeT i = 0; i < len; ++i) out >> v[i];
    return out;
}

}
