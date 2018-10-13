#pragma once

#include <enet/enet.h>
//
#include <lux_shared/common.hpp>
#include <lux_shared/net/serial.hpp>

LUX_MAY_FAIL send_packet(ENetPeer* peer, ENetPacket* pack, U8 channel);
LUX_MAY_FAIL create_reliable_pack(ENetPacket*& pack, SizeT sz);
LUX_MAY_FAIL create_unreliable_pack(ENetPacket*& pack, SizeT sz);

template<typename T>
LUX_MAY_FAIL send_net_data(ENetPeer* peer, T const& data, U8 channel) {
    ENetPacket* out_pack;
    if(create_reliable_pack(out_pack, get_real_sz(data)) != LUX_OK) {
        return LUX_FAIL;
    }

    U8* buff = out_pack->data;
    serialize(&buff, data);
    LUX_ASSERT(buff == out_pack->data + out_pack->dataLength);
    if(send_packet(peer, out_pack, channel) != LUX_OK) return LUX_FAIL;
    return LUX_OK;
}

template<typename T>
LUX_MAY_FAIL deserialize_packet(ENetPacket* in_pack, T* data) {
    U8 const* iter = in_pack->data;
    U8 const* end  = in_pack->data + in_pack->dataLength;
    if(deserialize(&iter, end, data) != LUX_OK) {
        return LUX_FAIL;
    }
    LUX_ASSERT(iter == end);
    return LUX_OK;
}
