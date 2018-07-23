#include <lux/serial/server_data.hpp>
#include <lux/serial/vector.hpp>
#include <lux/serial/array.hpp>
#include <lux/serial/vec_3.hpp>

namespace serial
{

SizeT get_size(TileData const &v)
{
    return get_size(v.db_hash);
}

SizeT get_size(ChunkData const &v)
{
    return get_size(v.pos) + get_size(v.tiles);
}

SizeT get_size(ServerData const &v)
{
    return get_size(v.chunks) +
           get_size(v.entities) +
           get_size(v.player_pos);
}

Serializer &operator<<(Serializer &in, TileData const &v)
{
    in << v.db_hash;
    return in;
}

Serializer &operator<<(Serializer &in, ChunkData const &v)
{
    in << v.pos;
    in << v.tiles;
    return in;
}

Serializer &operator<<(Serializer &in, ServerData const &v)
{
    in << v.chunks;
    in << v.entities;
    in << v.player_pos;
    return in;
}

Deserializer &operator>>(Deserializer &out, TileData &v)
{
    out >> v.db_hash;
    return out;
}

Deserializer &operator>>(Deserializer &out, ChunkData &v)
{
    out >> v.pos;
    out >> v.tiles;
    return out;
}

Deserializer &operator>>(Deserializer &out, ServerData &v)
{
    out >> v.chunks;
    out >> v.entities;
    out >> v.player_pos;
    return out;
}

}
