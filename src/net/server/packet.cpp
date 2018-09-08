#include <cassert>
//
#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>
#include <lux/net/get_size.hpp>
#include <lux/net/clear_buffer.hpp>
#include <lux/net/server/packet.hpp>

namespace net
{

using namespace server;

SizeT get_size(Packet const &v)
{
    SizeT size = get_size(v.type);
    switch(v.type)
    {
        case Packet::TICK:        size += get_size(v.tick);         break;
        case Packet::INIT:        size += get_size(v.init);         break;
        case Packet::CONF:        size += get_size(v.conf);         break;
        case Packet::MSG:         size += get_size(v.msg);          break;
        case Packet::MAP:         size += get_size(v.map);          break;
        case Packet::MAP_UPDATES: size += get_size(v.map_updates);  break;
        default: assert(false);
    }
    return size;
}

void clear_buffer(Packet &v)
{
    clear_buffer(v.type);

    clear_buffer(v.tick);
    clear_buffer(v.init);
    clear_buffer(v.conf);
    clear_buffer(v.msg);
    clear_buffer(v.map);
    clear_buffer(v.map_updates);
}

Serializer &operator<<(Serializer &in, Packet const &v)
{
    in << *(U8 const *)(&v.type);
    switch(v.type)
    {
        case Packet::TICK:        in << v.tick;        break;
        case Packet::INIT:        in << v.init;        break;
        case Packet::CONF:        in << v.conf;        break;
        case Packet::MSG:         in << v.msg;         break;
        case Packet::MAP:         in << v.map;         break;
        case Packet::MAP_UPDATES: in << v.map_updates; break;
        default: assert(false);
    }
    return in;
}

Deserializer &operator>>(Deserializer &out, Packet &v)
{
    out >> *(U8 *)(&v.type);
    switch(v.type)
    {
        case Packet::TICK:        out >> v.tick;        break;
        case Packet::INIT:        out >> v.init;        break;
        case Packet::CONF:        out >> v.conf;        break;
        case Packet::MSG:         out >> v.msg;         break;
        case Packet::MAP:         out >> v.map;         break;
        case Packet::MAP_UPDATES: out >> v.map_updates; break;
        default: assert(false);
    }
    return out;
}

}
