#pragma once

#include <lux_shared/common.hpp>
#include <lux_shared/net/common.hpp>
#include <lux_shared/map.hpp>
#include <lux_shared/entity.hpp>

#pragma pack(push, 1)

template<typename T>
struct NetDynArr {
    U32 len;
};

struct NetSsInit {
    Arr<U8, SERVER_NAME_LEN> name;
    U16 tick_rate;
};

struct NetSsTick {
    struct EntityComps {
        struct Pos {
            U32   id;
            Vec3F pos;
        };
        NetDynArr<Pos> pos;
    };
    U32            player_id;
    EntityComps    comps;
};

struct NetSsSgnl {
    struct MapLoad {
        struct Chunk {
            ChkPos pos;
            Arr<VoxelId , CHK_VOL> voxels;
            Arr<LightLvl, CHK_VOL> light_lvls;
        };
        NetDynArr<Chunk> chunks;
    };
    struct LightUpdate {
        struct Chunk {
            ChkPos pos;
            Arr<LightLvl, CHK_VOL> light_lvls;
        };
        NetDynArr<Chunk> chunks;
    };
    struct Msg {
        NetDynArr<char> contents;
    };
    enum Header : U8 {
        MAP_LOAD     = 0x00,
        LIGHT_UPDATE = 0x01,
        MSG          = 0x02,
        HEADER_MAX,
    } header;
    union {
        MapLoad     map_load;
        LightUpdate light_update;
        Msg         msg;
    };
};

struct NetCsTick {
    Vec2F player_dir;
};

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

struct NetCsSgnl {
    struct MapRequest {
        NetDynArr<ChkPos> requests;
    };
    struct Command {
        NetDynArr<char> contents;
    };
    enum Header : U8 {
        MAP_REQUEST = 0x00,
        COMMAND     = 0x01,
        HEADER_MAX,
    } header;
    union {
        MapRequest map_request;
        Command    command;
    };
};

#pragma pack(pop)
