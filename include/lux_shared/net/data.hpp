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
    struct EntityComps {
        typedef EntityVec Pos;
        typedef DynArr<char> Name;
        struct Visible {
            U32   visible_id;
            Vec2F quad_sz;
        };
        struct Item {
            F32 weight;
        };
        struct Destructible {
            F32 dur;
            F32 dur_max;
        };
        struct Health {
            F32 hp;
            F32 hp_max;
        };
        struct Container {
            DynArr<EntityHandle> items;
        };
        struct Orientation {
            F32 angle; ///in radians
        };

        HashTable<EntityHandle, Pos>          pos;
        HashTable<EntityHandle, Name>         name;
        HashTable<EntityHandle, Visible>      visible;
        HashTable<EntityHandle, Item>         item;
        HashTable<EntityHandle, Destructible> destructible;
        HashTable<EntityHandle, Health>       health;
        HashTable<EntityHandle, Container>    container;
        HashTable<EntityHandle, Orientation>  orientation;
    };
    EntityHandle         player_id;
    EntityComps          entity_comps;
    DynArr<EntityHandle> entities;
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
    } tag = TAG_MAX;

    MapLoad     map_load;
    LightUpdate light_update;
    Msg         msg;
};

struct NetCsTick {
    Vec2F player_dir;
    F32   player_aim_angle;
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
    } tag = TAG_MAX;

    MapRequest map_request;
    Command    command;
};
