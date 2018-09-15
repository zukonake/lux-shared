#pragma once

#include <enet/enet.h>
#include <lux_shared/common.hpp>

LuxRval send_packet(ENetPeer* peer, ENetHost *host,
                    Slice<U8> slice, U8 channel, U32 flags);
LuxRval send_init(ENetPeer* peer, ENetHost *host, Slice<U8> slice);
LuxRval send_tick(ENetPeer* peer, ENetHost *host, Slice<U8> slice);
LuxRval send_signal(ENetPeer* peer, ENetHost *host, Slice<U8> slice);
