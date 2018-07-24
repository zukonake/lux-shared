#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/hash.hpp>

namespace serial
{

class Serializer;
class Deserializer;

#pragma pack(push, 1)
struct TileData
{
    Hash db_hash;
};
#pragma pack(pop)

SizeT get_size(TileData const &v);
Serializer &operator<<(Serializer &in, TileData const &v);
Deserializer &operator>>(Deserializer &out, TileData &v);

}
