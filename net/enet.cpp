#include <zlib/zlib.h>
#include <enet/enet.h>
//
#include <lux_shared/common.hpp>
#include <lux_shared/net/common.hpp>
#include <lux_shared/net/serial.hpp>
#include <lux_shared/net/enet.hpp>

typedef U16 NetMagic;
NetMagic constexpr net_magic = 0x1337;
SizeT constexpr compression_threshold = -1;

///streams for zlib compression
z_stream net_def_strm;
z_stream net_inf_strm;

size_t compress(void *, const ENetBuffer *in_buffs, size_t in_buffs_num,
                size_t in_limit, enet_uint8 *out, size_t out_limit) {
    if(in_limit < compression_threshold) return 0;
    net_def_strm.avail_out = out_limit;
    net_def_strm.next_out = (Bytef*)out;
    while(in_buffs_num > 1) {
        if(in_buffs->dataLength > 0) {
            net_def_strm.avail_in = in_buffs->dataLength;
            net_def_strm.next_in  = (Bytef*)in_buffs->data;

            LUX_ASSERT(deflate(&net_def_strm, Z_NO_FLUSH) != Z_STREAM_ERROR);
        }
        in_buffs++;
        in_buffs_num--;
    }
    net_def_strm.avail_in = in_buffs->dataLength;
    net_def_strm.next_in  = (Bytef*)in_buffs->data;
    auto ret = deflate(&net_def_strm, Z_FINISH);
    LUX_ASSERT(ret != Z_STREAM_ERROR);
    SizeT total = net_def_strm.total_out;
    deflateReset(&net_def_strm);
    if(ret != Z_STREAM_END) {
        LUX_LOG_WARN("failed to compress %zuB into %zuB",
                     in_limit, out_limit);
        return 0;
    }
    LUX_ASSERT(net_def_strm.avail_in == 0);
    return total;
}

size_t decompress(void *, const enet_uint8 *in, size_t in_limit,
                  enet_uint8 *out, size_t out_limit) {
    net_inf_strm.avail_out = out_limit;
    net_inf_strm.next_out = (Bytef*)out;
    net_inf_strm.avail_in = in_limit;
    net_inf_strm.next_in  = (Bytef*)in;

    auto ret = inflate(&net_inf_strm, Z_FINISH);
    LUX_ASSERT(ret != Z_STREAM_ERROR);
    SizeT total = net_inf_strm.total_out;
    inflateReset(&net_inf_strm);
    if(ret != Z_STREAM_END) {
        LUX_LOG_WARN("failed to decompress %zuB into %zuB",
                     in_limit, out_limit);
        return 0;
    }
    LUX_ASSERT(net_inf_strm.avail_in == 0);
    return total;
}

static void net_deinit(void*) {
    deflateEnd(&net_def_strm);
    inflateEnd(&net_inf_strm);
}

void net_compression_init(ENetHost* host) {
    net_def_strm.zalloc = Z_NULL;
    net_def_strm.zfree  = Z_NULL;
    net_def_strm.opaque = Z_NULL;
    deflateInit(&net_def_strm, Z_DEFAULT_COMPRESSION);

    net_inf_strm.zalloc = Z_NULL;
    net_inf_strm.zfree  = Z_NULL;
    net_inf_strm.opaque = Z_NULL;
    inflateInit(&net_inf_strm);

    static ENetCompressor compressor;
    compressor.compress = &compress;
    compressor.decompress = &decompress;
    compressor.context = (void*)1; ///according to docs, has to be non-zero
    compressor.destroy = &net_deinit;

    enet_host_compress(host, &compressor);
}

LUX_MAY_FAIL create_pack(ENetPacket** pack, SizeT sz, U32 flags) {
    *pack = enet_packet_create(nullptr, sz, flags);
    if(*pack == nullptr) {
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

template<typename T>
LUX_MAY_FAIL send_net_data(ENetPeer* peer, T* data,
                           U8 channel, bool clear) {
    ENetPacket* out_pack;
    int packet_flags = 0;
    switch(channel) {
        //@TODO, this might be very bad for chunk transfer
        case SGNL_CHANNEL:
        case INIT_CHANNEL: packet_flags = ENET_PACKET_FLAG_RELIABLE; break;

        case TICK_CHANNEL: packet_flags = ENET_PACKET_FLAG_UNSEQUENCED; break;
        default: break;
    }
    LUX_RETHROW(create_pack(&out_pack, get_real_sz(*data) + sizeof(NetMagic),
                packet_flags), "failed to create packet");
    U8* buff_iter = out_pack->data;
    serialize(&buff_iter, net_magic);
    serialize(&buff_iter, *data);
    LUX_ASSERT(buff_iter == out_pack->data + out_pack->dataLength);
    if(clear) {
        clear_net_data(data);
    }
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
    LUX_RETHROW(deserialize(&iter, end, data),
                "failed to deserialize packet");
    //@TODO LUX_HEX_DUMP or something
    if(iter < end) {
        LUX_LOG_ERR("trailing %zuB after deserialization", end - iter);
        return LUX_FAIL;
    }
    return LUX_OK;
}

#include <lux_shared/net/data.hpp>
#include <lux_shared/net/data.inl>

template LUX_MAY_FAIL send_net_data<NetSsInit>(ENetPeer*, NetSsInit*, U8, bool);
template LUX_MAY_FAIL send_net_data<NetSsTick>(ENetPeer*, NetSsTick*, U8, bool);
template LUX_MAY_FAIL send_net_data<NetSsSgnl>(ENetPeer*, NetSsSgnl*, U8, bool);
template LUX_MAY_FAIL send_net_data<NetCsInit>(ENetPeer*, NetCsInit*, U8, bool);
template LUX_MAY_FAIL send_net_data<NetCsTick>(ENetPeer*, NetCsTick*, U8, bool);
template LUX_MAY_FAIL send_net_data<NetCsSgnl>(ENetPeer*, NetCsSgnl*, U8, bool);

template LUX_MAY_FAIL deserialize_packet<NetSsInit>(ENetPacket*, NetSsInit*);
template LUX_MAY_FAIL deserialize_packet<NetSsTick>(ENetPacket*, NetSsTick*);
template LUX_MAY_FAIL deserialize_packet<NetSsSgnl>(ENetPacket*, NetSsSgnl*);
template LUX_MAY_FAIL deserialize_packet<NetCsInit>(ENetPacket*, NetCsInit*);
template LUX_MAY_FAIL deserialize_packet<NetCsTick>(ENetPacket*, NetCsTick*);
template LUX_MAY_FAIL deserialize_packet<NetCsSgnl>(ENetPacket*, NetCsSgnl*);

