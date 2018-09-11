#pragma once

#include <lux/net/clear_buffer.hpp>
#include <lux/net/deserializer.hpp>

namespace net
{

template<typename Buff>
void Deserializer::deserialize_packet(ENetPacket *pack, Buff &buff)
{
    this->set_slice(pack->data, pack->data + pack->dataLength);
    net::clear_buffer(buff);
    *this >> buff;
    enet_packet_destroy(pack);
}

}
