#include <lux/serial/client_data.hpp>
#include <lux/serial/vec_2.hpp>
#include <lux/serial/vec_3.hpp>
#include <lux/serial/vector.hpp>

namespace serial
{

Serializer &operator<<(Serializer &in, ClientData const &v)
{
    in << v.chunk_requests;
    in << v.character_dir;
    in << v.is_moving;
    return in;
}

Deserializer &operator>>(Deserializer &out, ClientData &v)
{
    out >> v.chunk_requests;
    out >> v.character_dir;
    out >> v.is_moving;
    return out;
}

}
