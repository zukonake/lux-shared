#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>
#include <lux/net/get_size.hpp>
#include <lux/net/clear_buffer.hpp>
#include <lux/net/client/signal.hpp>

namespace net
{

using namespace client;

SizeT get_size(Signal const &v)
{
    return get_size(v.type);
}

void clear_buffer(Signal &v)
{
    clear_buffer(v.type);
}

Serializer &operator<<(Serializer &in, Signal const &v)
{
    in << *(U8 const *)(&v.type);
    return in;
}

Deserializer &operator>>(Deserializer &out, Signal &v)
{
    out >> *(U8 *)(&v.type);
    return out;
}

}
