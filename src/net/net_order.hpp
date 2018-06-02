#pragma once

#include <cstdint>

namespace net
{

template<typename T>
T net_order(T val);

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

//TODO use BSWAP asm instruction?
template<>
inline uint8_t net_order(uint8_t val)
{
    return val;
}

template<>
inline uint16_t net_order(uint16_t val)
{
    return ((val & 0x00FF) << 8) |
           ((val & 0xFF00) >> 8);
}

template<>
inline uint32_t net_order(uint32_t val)
{
    return ((val & 0x000000FF) << 24) |
           ((val & 0x0000FF00) <<  8) |
           ((val & 0x00FF0000) >>  8) |
           ((val & 0xFF000000) >> 24);
}

template<>
inline uint64_t net_order(uint64_t val)
{
    return ((val & 0x00000000000000FF) << 56) |
           ((val & 0x000000000000FF00) << 40) |
           ((val & 0x0000000000FF0000) << 24) |
           ((val & 0x00000000FF000000) <<  8) |
           ((val & 0x000000FF00000000) >>  8) |
           ((val & 0x0000FF0000000000) >> 24) |
           ((val & 0x00FF000000000000) >> 40) |
           ((val & 0xFF00000000000000) >> 56);
}

#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

template<typename T>
T net_order(T val)
{
    return val;
}

#else
#error "invalid byte order"
#endif

}
