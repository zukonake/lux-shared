#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/hash.hpp>
#include <lux/serial/serializer.hpp>
#include <lux/serial/deserializer.hpp>
#include <lux/serial/get_size.hpp>
#include <lux/serial/clear_buffer.hpp>

namespace serial
{

#pragma pack(push, 1)
struct TileData
{
    Hash db_hash;
};
#pragma pack(pop)

inline SizeT get_size(TileData const &v)
{
    return get_size(v.db_hash);
}

inline void clear_buffer(TileData &v)
{
    clear_buffer(v.db_hash);
}

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
