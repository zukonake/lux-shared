#include <enet/enet.h>
//
#include <lux_shared/common.hpp>
#include <lux_shared/net/common.hpp>
#include <lux_shared/net/enet.hpp>

LUX_MAY_FAIL create_pack(ENetPacket*& pack, SizeT sz, U32 flags) {
    pack = enet_packet_create(nullptr, sz, flags);
    if(pack == nullptr) {
        LUX_LOG_ERR("failed to create enet packet");
        LUX_LOG_ERR("    data size: %zuB", sz);
        LUX_LOG_ERR("    flags: %x", flags);
        return LUX_FAIL;
    }
    return LUX_OK;
}

LUX_MAY_FAIL send_packet(ENetPeer* peer, ENetPacket* pack, U8 channel) {
    if(enet_peer_send(peer, channel, pack) < 0) {
        U8* ip = get_ip(peer->address);
        LUX_LOG_ERR("failed to send enet packet");
        LUX_LOG_ERR("    data size: %zuB", pack->dataLength);
        LUX_LOG_ERR("    channel: %u", channel);
        LUX_LOG_ERR("    peer ip: %u.%u.%u.%u", ip[0], ip[1], ip[2], ip[4]);
        LUX_LOG_ERR("    peer data: %zu", (SizeT)peer->data);
        return LUX_FAIL;
    }
    return LUX_OK;
}

LUX_MAY_FAIL create_reliable_pack(ENetPacket*& pack, SizeT sz) {
    return create_pack(pack, sz, ENET_PACKET_FLAG_RELIABLE);
}

LUX_MAY_FAIL create_unreliable_pack(ENetPacket*& pack, SizeT sz) {
    return create_pack(pack, sz, ENET_PACKET_FLAG_UNSEQUENCED);
}
