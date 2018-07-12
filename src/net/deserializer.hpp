#pragma once

#include <cassert>
//
#include <alias/int.hpp>
#include <net/net_order.hpp>

namespace net
{

class Deserializer
{
    public:
    Deserializer(U8 const *arr, U8 const *end);

    template<typename T>
    void  pop(T &val);
    SizeT get_size() const;

    private:
    U8 const *arr;
    U8 const *end;
};

template<>
inline void Deserializer::pop<U8>(U8 &val)
{
    assert(get_size() > 0);
    val = *(arr++);
}

template<>
inline void Deserializer::pop<bool>(bool &val)
{
    U8 temp;
    pop<U8>(temp);
    val = (bool)temp;
}

template<>
inline void Deserializer::pop<U16>(U16 &val)
{
    U8 temp;
    pop<U8>(temp);
    val  = (U16)temp;
    pop<U8>(temp);
    val |= (U16)((U16)temp << 8);
    val = net_order<U16>(val);
}

template<>
inline void Deserializer::pop<U32>(U32 &val)
{
    U8 temp;
    pop<U8>(temp);
    val  = (U32)temp;
    pop<U8>(temp);
    val |= (U32)temp << 8;
    pop<U8>(temp);
    val |= (U32)temp << 16;
    pop<U8>(temp);
    val |= (U32)temp << 24;
    val = net_order<U32>(val);
}

template<>
inline void Deserializer::pop<U64>(U64 &val)
{
    U8 temp;
    pop<U8>(temp);
    val  = (U64)temp;
    pop<U8>(temp);
    val |= (U64)temp << 8;
    pop<U8>(temp);
    val |= (U64)temp << 16;
    pop<U8>(temp);
    val |= (U64)temp << 24;
    pop<U8>(temp);
    val |= (U64)temp << 32;
    pop<U8>(temp);
    val |= (U64)temp << 40;
    pop<U8>(temp);
    val |= (U64)temp << 48;
    pop<U8>(temp);
    val |= (U64)temp << 56;
    val = net_order<U64>(val);
}

}
