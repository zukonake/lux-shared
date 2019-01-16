#pragma once

#include <enet/enet.h>
//
#include <zlib/zlib.h>
//
#include <lux_shared/common.hpp>
#include <lux_shared/net/common.hpp>

void net_compression_init(ENetHost* host);

LUX_MAY_FAIL send_packet(ENetPeer* peer, ENetPacket* pack, U8 channel);
LUX_MAY_FAIL create_reliable_pack(ENetPacket*& pack, SizeT sz);
LUX_MAY_FAIL create_unreliable_pack(ENetPacket*& pack, SizeT sz);

template<typename T>
LUX_MAY_FAIL send_net_data(ENetPeer* peer, T* data,
                           U8 channel, bool clear = true);
template<typename T>
LUX_MAY_FAIL deserialize_packet(ENetPacket* in_pack, T* data);

