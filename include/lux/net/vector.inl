#pragma once

#include <type_traits>
//
#include <lux/alias/scalar.hpp>
#include <lux/alias/vector.hpp>
#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>
#include <lux/net/get_size.hpp>
#include <lux/net/clear_buffer.hpp>

namespace net
{

template<typename T>
SizeT get_size(Vector<T> const &v)
{
    SizeT size = sizeof(SizeT); /* first, the size of the vector gets sent */
    if constexpr(std::is_trivial<T>::value)
    {
        return size + sizeof(T) * v.size();
    }
    else
    {
        for(auto const &i : v) size += get_size(i);
        return size;
    }
}

template<typename T>
void clear_buffer(Vector<T> &v)
{
    if constexpr(std::is_trivial<T>::value == false)
    {
        for(auto &i : v) clear_buffer(i);
    }
    v.clear();
}

template<typename T>
Serializer &operator<<(Serializer &in, Vector<T> const &v)
{
    in << v.size();
    for(auto const &i : v) in << i;
    return in;
}

template<typename T>
Deserializer &operator>>(Deserializer &out, Vector<T> &v)
{
    SizeT len;
    out >> len;
    v.resize(len);
    for(SizeT i = 0; i < len; ++i) out >> v[i];
    return out;
}

}
