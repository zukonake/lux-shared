#pragma once

#include <alias/int.hpp>
#include <net/net_order.hpp>

namespace net
{

class Serializer
{
    public:
    Serializer(SizeT len);
    ~Serializer();

    template<typename T>
    void  push(T const &val);
    SizeT get_size() const;
    U8   *get() const;

    private:
    SizeT iter;
    U8   *arr;
};

template<>
inline void Serializer::push<U8>(U8 const &val)
{
    arr[iter++] = val;
}

template<>
inline void Serializer::push<bool>(bool const &val)
{
    push<U8>((U8)val);
}

template<>
inline void Serializer::push<U16>(U16 const &val)
{
    U16 temp = net_order<U16>(val);
    push<U8>( temp & 0x00FF);
    push<U8>((temp & 0xFF00) >> 8U);
}

template<>
inline void Serializer::push<U32>(U32 const &val)
{
    U32 temp = net_order<U32>(val);
    push<U8>( temp & 0x000000FF);
    push<U8>((temp & 0x0000FF00) >>  8UL);
    push<U8>((temp & 0x00FF0000) >> 16UL);
    push<U8>((temp & 0xFF000000) >> 24UL);
}

template<>
inline void Serializer::push<U64>(U64 const &val)
{
    U64 temp = net_order<U64>(val);
    push<U8>( temp & 0x00000000000000FF);
    push<U8>((temp & 0x000000000000FF00) >>  8ULL);
    push<U8>((temp & 0x0000000000FF0000) >> 16ULL);
    push<U8>((temp & 0x00000000FF000000) >> 24ULL);
    push<U8>((temp & 0x000000FF00000000) >> 32ULL);
    push<U8>((temp & 0x0000FF0000000000) >> 40ULL);
    push<U8>((temp & 0x00FF000000000000) >> 48ULL);
    push<U8>((temp & 0xFF00000000000000) >> 56ULL);
}

}
