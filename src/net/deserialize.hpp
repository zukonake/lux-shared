#pragma once

#include <alias/int.hpp>
#include <alias/vector.hpp>
#include <net/net_order.hpp>

namespace net
{

template<typename T>
void deserialize(Vector<U8> &bytes, T &val);

template<>
void deserialize<bool>(Vector<U8> &bytes, bool &val)
{
    val = (bool)bytes.back();
    bytes.pop_back();
}

template<>
void deserialize<U8>(Vector<U8> &bytes, U8 &val)
{
    val = (U8)bytes.back();
    bytes.pop_back();
}

template<>
void deserialize<U16>(Vector<U8> &bytes, U16 &val)
{
    val = 0;
    val |= (U16)(bytes.back()) << 8;
    bytes.pop_back();
    val |= (U16)bytes.back();
    bytes.pop_back();
    val = net_order<U16>(val);
}

template<>
void deserialize<U32>(Vector<U8> &bytes, U32 &val)
{
    val = 0;
    val |= (U32)(bytes.back()) << 24;
    bytes.pop_back();
    val |= (U32)(bytes.back()) << 16;
    bytes.pop_back();
    val |= (U32)(bytes.back()) << 8;
    bytes.pop_back();
    val |= (U32)bytes.back();
    bytes.pop_back();
    val = net_order<U32>(val);
}

template<>
void deserialize<U64>(Vector<U8> &bytes, U64 &val)
{
    val = 0;
    val |= (U64)(bytes.back()) << 56;
    bytes.pop_back();
    val |= (U64)(bytes.back()) << 48;
    bytes.pop_back();
    val |= (U64)(bytes.back()) << 40;
    bytes.pop_back();
    val |= (U64)(bytes.back()) << 32;
    bytes.pop_back();
    val |= (U64)(bytes.back()) << 24;
    bytes.pop_back();
    val |= (U64)(bytes.back()) << 16;
    bytes.pop_back();
    val |= (U64)(bytes.back()) << 8;
    bytes.pop_back();
    val |= (U64)bytes.back();
    bytes.pop_back();
    val = net_order<U64>(val);
}

}
