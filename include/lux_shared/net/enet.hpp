#pragma once

#include <enet/enet.h>
//
#include <lux_shared/common.hpp>
#include <lux_shared/net/common.hpp>
#include <lux_shared/net/serial.hpp>

LUX_MAY_FAIL send_packet(ENetPeer* peer, ENetPacket* pack, U8 channel);
LUX_MAY_FAIL create_reliable_pack(ENetPacket*& pack, SizeT sz);
LUX_MAY_FAIL create_unreliable_pack(ENetPacket*& pack, SizeT sz);

template<typename T>
LUX_MAY_FAIL send_net_data(ENetPeer* peer, T* data,
                           U8 channel, bool clear = true) {
    ENetPacket* out_pack;
    LUX_RETHROW(create_reliable_pack(out_pack,
                                     get_real_sz(*data) + sizeof(NetMagic)),
        "failed to create packet for net data");

    U8* buff = out_pack->data;
    serialize(&buff, net_magic);
    serialize(&buff, *data);
    if(clear) {
        clear_net_data(data);
    }
    LUX_ASSERT(buff == out_pack->data + out_pack->dataLength);
    LUX_RETHROW(send_packet(peer, out_pack, channel),
        "failed to send net data");
    return LUX_OK;
}

template<typename T>
LUX_MAY_FAIL deserialize_packet(ENetPacket* in_pack, T* data) {
    clear_net_data(data);
    U8 const* iter = in_pack->data;
    U8 const* end  = in_pack->data + in_pack->dataLength;
    NetMagic magic;
    LUX_RETHROW(deserialize(&iter, end, &magic),
        "failed to deserialize magic header");
    if(magic != net_magic) {
        LUX_LOG_ERR("invalid magic header %04x instead of %04x",
                    magic, net_magic);
        return LUX_FAIL;
    }
    LUX_RETHROW(deserialize(&iter, end, data), "failed to deserialize packet");
    //@TODO LUX_HEX_DUMP or something
    if(iter < end) {
        LUX_LOG_ERR("trailing %zuB after deserialization", end - iter);
        return LUX_FAIL;
    }
    return LUX_OK;
}
