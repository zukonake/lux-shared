#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/hash.hpp>

namespace serial
{

#pragma pack(push, 1)
struct TileData
{
    Hash db_hash;
};
#pragma pack(pop)

class Serializer;
class Deserializer;

SizeT get_size(TileData const &v);
void clear_buffer(TileData &v);
Serializer &operator<<(Serializer &in, TileData const &v);
Deserializer &operator>>(Deserializer &out, TileData &v);

}
