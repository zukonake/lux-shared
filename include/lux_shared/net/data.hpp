#pragma once

#include <lux_shared/common.hpp>
#include <lux_shared/net/common.hpp>
#include <lux_shared/net/serial.hpp>
#include <lux_shared/map.hpp>
#include <lux_shared/entity.hpp>

//@TODO improve - use buffers
//@TODO disable packing
#pragma pack(push, 1)

#define LUX_NET_DATA_STT(ident) \
    template<> \
    struct HasStaticSz<ident> { bool static constexpr val = true; }; \
    LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end, ident*); \
    void serialize(U8** buff, ident const&)
#define LUX_NET_DATA_DYN(ident) \
    SizeT get_real_sz(ident const& val); \
    LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end, ident*); \
    void serialize(U8** buff, ident const&)

typedef U16 NetMagic;
NetMagic constexpr net_magic = 0x1337;

//LUX_NET_DATA_STT(EntityComps::Pos); //typedef
//LUX_NET_DATA_STT(EntityComps::Vel); //typedef
LUX_NET_DATA_STT(EntityComps::Shape);
LUX_NET_DATA_STT(EntityComps::Visible);
LUX_NET_DATA_STT(EntityComps::Item);
LUX_NET_DATA_STT(EntityComps::Destructible);
LUX_NET_DATA_STT(EntityComps::Animated);
LUX_NET_DATA_DYN(EntityComps);

struct NetSsInit {
    Arr<U8, SERVER_NAME_LEN> name;
    U16                 tick_rate;
};
LUX_NET_DATA_STT(NetSsInit);

struct NetSsTick {
    EntityHandle player_id;
    EntityComps  comps;
};
LUX_NET_DATA_DYN(NetSsTick);

struct NetSsSgnl {
    struct MapLoad {
        struct Chunk {
            Arr<VoxelId , CHK_VOL> voxels;
            Arr<LightLvl, CHK_VOL> light_lvls;
        };
        VecMap<ChkPos, Chunk> chunks;
    };
    struct LightUpdate {
        struct Chunk {
            Arr<LightLvl, CHK_VOL> light_lvls;
        };
        VecMap<ChkPos, Chunk> chunks;
    };
    struct Msg {
        DynArr<char> contents;
    };
    enum Header : U8 {
        MAP_LOAD     = 0x00,
        LIGHT_UPDATE = 0x01,
        MSG          = 0x02,
        HEADER_MAX,
    } header;

    MapLoad     map_load;
    LightUpdate light_update;
    Msg         msg;
};
LUX_NET_DATA_STT(NetSsSgnl::MapLoad::Chunk);
LUX_NET_DATA_STT(NetSsSgnl::LightUpdate::Chunk);
LUX_NET_DATA_DYN(NetSsSgnl);

struct NetCsTick {
    Vec2F player_dir;
};
LUX_NET_DATA_STT(NetCsTick);

struct NetCsInit {
    struct {
        U8 major;
        U8 minor;
        U8 patch;
        static_assert(sizeof(major) == sizeof(NET_VERSION_MAJOR));
        static_assert(sizeof(minor) == sizeof(NET_VERSION_MINOR));
        static_assert(sizeof(patch) == sizeof(NET_VERSION_PATCH));
    } net_ver;
    Arr<U8, CLIENT_NAME_LEN> name;
};
LUX_NET_DATA_STT(NetCsInit);

struct NetCsSgnl {
    struct MapRequest {
        VecSet<ChkPos> requests;
    };
    struct Command {
        DynArr<char> contents;
    };
    enum Header : U8 {
        MAP_REQUEST = 0x00,
        COMMAND     = 0x01,
        HEADER_MAX,
    } header;

    MapRequest map_request;
    Command    command;
};
LUX_NET_DATA_DYN(NetCsSgnl);

#ifndef LUX_NET_DATA_STT
    #pragma message("cleanup here")
#endif
#ifndef LUX_NET_DATA_DYN
    #pragma message("cleanup here")
#endif
#undef LUX_NET_DATA_STT
#undef LUX_NET_DATA_DYN

#pragma pack(pop)
