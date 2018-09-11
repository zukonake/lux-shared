#pragma once

#include <lux/net/get_size.hpp>
#include <lux/net/clear_buffer.hpp>
#include <lux/net/serializer.hpp>

namespace net
{

template<typename Buff>
void Serializer::serialize_packet(ENetPacket *pack, Buff &buff)
{
    this->reserve(net::get_size(buff));
    *this << buff;
    net::clear_buffer(buff);
    //TODO for some reason data is not transferred correctly when
    //ENET_PACKET_FLAG_NO_ALLOCATE is set
    //without it it's quite slow, the data is allocated per-packet instead of
    //using a buffer, and also it is copied
    if(enet_packet_resize(pack, this->get_used()) < 0) {
        LUX_LOG("SERIALIZER", FATAL, "packet resize failed");
    }
    pack->data = (enet_uint8 *)this->get();
}

}
