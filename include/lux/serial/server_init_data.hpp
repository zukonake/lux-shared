#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/vector.hpp>

namespace serial
{

#pragma pack(push, 1)
struct ServerInitData
{
    F64                 tick_rate;
    Vector<char>        server_name;
};
#pragma pack(pop)

class Serializer;
class Deserializer;

SizeT get_size(ServerInitData const &v);
void clear_buffer(ServerInitData &v);
Serializer &operator<<(Serializer &in, ServerInitData const &v);
Deserializer &operator>>(Deserializer &out, ServerInitData &v);

}
