#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>
#include <lux/net/get_size.hpp>
#include <lux/net/clear_buffer.hpp>
#include <lux/net/vector.inl>
#include <lux/net/server/msg.hpp>

namespace net
{

using namespace server;

SizeT get_size(Msg const &v)
{
    return get_size(v.log_level) + get_size(v.log_msg);
}

void clear_buffer(Msg &v)
{
    clear_buffer(v.log_level);
    clear_buffer(v.log_msg);
}

Serializer &operator<<(Serializer &in, Msg const &v)
{
    in << *((U8 const *)&v.log_level);
    in << v.log_msg;
    return in;
}

Deserializer &operator>>(Deserializer &out, Msg &v)
{
    out >> *((U8 *)&v.log_level);
    out >> v.log_msg;
    return out;
}

}
