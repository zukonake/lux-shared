#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/vector.hpp>
#include <lux/linear/vec_2.hpp>
#include <lux/serial/serializer.hpp>
#include <lux/serial/deserializer.hpp>
#include <lux/serial/get_size.hpp>
#include <lux/serial/clear_buffer.hpp>
#include <lux/serial/vec_2.hpp>
#include <lux/serial/vec_3.hpp>
#include <lux/serial/vector.hpp>
#include <lux/common/chunk.hpp>

namespace serial
{

#pragma pack(push, 1)
struct ClientData
{
    Vector<chunk::Pos> chunk_requests;
    linear::Vec2<F32>  character_dir;
    bool               is_moving;
};
#pragma pack(pop)

inline SizeT get_size(ClientData const &v)
{
    return get_size(v.chunk_requests) +
           get_size(v.character_dir) +
           get_size(v.is_moving);
}

inline void clear_buffer(ClientData &v)
{
    clear_buffer(v.chunk_requests);
    clear_buffer(v.character_dir);
    clear_buffer(v.is_moving);
}

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
