#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/vector.hpp>

namespace serial
{

class Serializer;
class Deserializer;

#pragma pack(push, 1)
struct ServerInitData
{
    F64                 tick_rate;
    Vector<char>        server_name;
};
#pragma pack(pop)

SizeT get_size(ServerInitData const &v);
Serializer   &operator<<(Serializer   &in, ServerInitData const &v);
Deserializer &operator>>(Deserializer &in, ServerInitData       &v);

}
