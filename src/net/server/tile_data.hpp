#pragma once

#include <net/hash.hpp>

namespace net
{

#pragma pack(push, 1)
struct TileData
{
    Hash db_hash;
};
#pragma pack(pop)

inline Serializer &operator<<(Serializer &in, TileData const &v)
{
    in << v.db_hash;
    return in;
}

inline Deserializer &operator>>(Deserializer &out, TileData &v)
{
    out >> v.db_hash;
    return out;
}

}
