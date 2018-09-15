#pragma once

#include <lux_shared/common.hpp>
#include <lux_shared/map.hpp>
#include <lux_shared/entity.hpp>

#pragma pack(push, 1)

template<typename T>
struct NetDynArr {
    U32 len;
    T*  val;
};

struct NetServerInit {
    Arr<U8, SERVER_NAME_LEN> name;
    U16 tick_rate;
};

struct NetServerTick {
    EntityVec player_pos;
};

struct NetServerSignal {
    struct MapLoad {
        struct Chunk {
            ChkPos pos;
            Arr<VoxelId , CHK_VOL> voxels;
            Arr<LightLvl, CHK_VOL> light_lvls;
        };
        NetDynArr<Chunk> chunks;
    };
    enum Type : U8 {
        MAP_LOAD = 0x00,
    } type;
    union {
        MapLoad map_load;
    };
};

struct NetClientInit {
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

struct NetClientSignal {
    struct MapRequest {
        NetDynArr<ChkPos> requests;
    };
    enum Type : U8 {
        MAP_REQUEST = 0x00,
    } type;
    union {
        MapRequest map_request;
    };
};

#pragma pack(pop)
