#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/linear/vec_2.hpp>
#include <lux/net/array.hpp>
#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>
#include <lux/common/chunk.hpp>

namespace net
{

#pragma pack(push, 1)
struct ClientData
{
    Array<ChunkPos>   chunk_requests;
    linear::Vec2<F32> character_dir;
    bool              is_moving;
};
#pragma pack(pop)

inline Serializer &operator<<(Serializer &in, ClientData const &v)
{
    in << v.chunk_requests;
    in << v.character_dir;
    in << v.is_moving;
    return in;
}

inline Deserializer &operator>>(Deserializer &out, ClientData &v)
{
    out >> v.chunk_requests;
    out >> v.character_dir;
    out >> v.is_moving;
    return out;
}

}
