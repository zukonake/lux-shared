#include <cassert>
//
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
    SizeT size = get_size(v.type);
    switch(v.type)
    {
        case Signal::CONF: size += get_size(v.conf); break;
        default: assert(false);
    }
    return size;
}

void clear_buffer(Signal &v)
{
    clear_buffer(v.type);

    clear_buffer(v.conf);
}

Serializer &operator<<(Serializer &in, Signal const &v)
{
    in << *(U8 const *)(&v.type);
    switch(v.type)
    {
        case Signal::CONF: in << v.conf; break;
        default: assert(false);
    }
    return in;
}

Deserializer &operator>>(Deserializer &out, Signal &v)
{
    out >> *(U8 *)(&v.type);
    switch(v.type)
    {
        case Signal::CONF: out >> v.conf; break;
        default: assert(false);
    }
    return out;
}

}
