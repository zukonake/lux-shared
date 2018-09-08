#pragma once

#include <type_traits>
//
#include <lux/alias/scalar.hpp>
#include <lux/alias/array.hpp>
#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>
#include <lux/net/get_size.hpp>
#include <lux/net/clear_buffer.hpp>

namespace net
{

template<typename T, SizeT len>
SizeT get_size(Array<T, len> const &v)
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
void clear_buffer(Array<T, len> &v)
{
    if constexpr(std::is_trivial<T>::value == false)
    {
        for(auto &i : v) clear_buffer(i);
    }
}

template<typename T, SizeT len>
Serializer &operator<<(Serializer &in, Array<T, len> const &v)
{
    for(SizeT i = 0; i < len; ++i) in << v[i];
    return in;
}

template<typename T, SizeT len>
Deserializer &operator>>(Deserializer &out, Array<T, len> &v)
{
    for(SizeT i = 0; i < len; ++i) out >> v[i];
    return out;
}

}
