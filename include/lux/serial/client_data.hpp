#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/vector.hpp>
#include <lux/linear/vec_2.hpp>
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

class Serializer;
class Deserializer;

SizeT get_size(ClientData const &v);
void clear_buffer(ClientData &v);
Serializer &operator<<(Serializer &in, ClientData const &v);
Deserializer &operator>>(Deserializer &out, ClientData &v);

}
