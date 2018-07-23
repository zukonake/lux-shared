#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/vector.hpp>
#include <lux/linear/vec_2.hpp>
#include <lux/serial/serializer.hpp>
#include <lux/serial/deserializer.hpp>
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

SizeT get_size(ClientData const &v);
Serializer &operator<<(Serializer &in, ClientData const &v);
Deserializer &operator>>(Deserializer &out, ClientData &v);

}
