#pragma once

#include <alias/int.hpp>
#include <alias/vector.hpp>
#include <net/net_order.hpp>

namespace net
{

template<typename T>
void serialize(Vector<U8> &bytes, T const &val);

template<>
void serialize<bool>(Vector<U8> &bytes, bool const &val)
{
    bytes.emplace_back(val);
}

template<>
void serialize<U8>(Vector<U8> &bytes, U8 const &val)
{
    bytes.emplace_back(val);
}

template<>
void serialize<U16>(Vector<U8> &bytes, U16 const &val)
{
    U16 temp = net_order<U16>(val);
    bytes.emplace_back( temp & 0x00FF);
    bytes.emplace_back((temp & 0xFF00) >> 8);
}

template<>
void serialize<U32>(Vector<U8> &bytes, U32 const &val)
{
    U32 temp = net_order<U32>(val);
    bytes.emplace_back( temp & 0x000000FF);
    bytes.emplace_back((temp & 0x0000FF00) >>  8);
    bytes.emplace_back((temp & 0x00FF0000) >> 16);
    bytes.emplace_back((temp & 0xFF000000) >> 24);
}

template<>
void serialize<U64>(Vector<U8> &bytes, U64 const &val)
{
    U64 temp = net_order<U64>(val);
    bytes.emplace_back( temp & 0x00000000000000FF);
    bytes.emplace_back((temp & 0x000000000000FF00) >>  8);
    bytes.emplace_back((temp & 0x0000000000FF0000) >> 16);
    bytes.emplace_back((temp & 0x00000000FF000000) >> 24);
    bytes.emplace_back((temp & 0x000000FF00000000) >> 32);
    bytes.emplace_back((temp & 0x0000FF0000000000) >> 40);
    bytes.emplace_back((temp & 0x00FF000000000000) >> 48);
    bytes.emplace_back((temp & 0xFF00000000000000) >> 56);
}

}
