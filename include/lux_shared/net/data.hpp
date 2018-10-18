#pragma once

#include <lux_shared/common.hpp>
#include <lux_shared/net/common.hpp>
#include <lux_shared/net/serial.hpp>
#include <lux_shared/map.hpp>
#include <lux_shared/entity.hpp>

struct NetSsInit {
    Arr<U8, SERVER_NAME_LEN> name;
    U16                 tick_rate;
};

struct NetSsTick {
    EntityHandle player_id;
    EntityComps  comps;
};

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
    enum Tag : U8 {
        MAP_LOAD     = 0x00,
        LIGHT_UPDATE = 0x01,
        MSG          = 0x02,
        TAG_MAX,
    } tag;

    MapLoad     map_load;
    LightUpdate light_update;
    Msg         msg;
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
        VecSet<ChkPos> requests;
    };
    struct Command {
        DynArr<char> contents;
    };
    enum Tag : U8 {
        MAP_REQUEST = 0x00,
        COMMAND     = 0x01,
        TAG_MAX,
    } tag;

    MapRequest map_request;
    Command    command;
};
