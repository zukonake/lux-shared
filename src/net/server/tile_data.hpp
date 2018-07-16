#pragma once

#include <net/hash.hpp>

namespace net
{

#pragma pack(push, 1)
struct TileData
{
    Hash database_hash;
};
#pragma pack(pop)

inline Serializer &operator<<(Serializer &in, TileData const &v)
{
    in << v.database_hash;
    return in;
}

inline Deserializer &operator>>(Deserializer &out, TileData &v)
{
    out >> v.database_hash;
    return out;
}

}
