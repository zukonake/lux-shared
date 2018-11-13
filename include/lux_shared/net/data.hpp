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
            DynArr<EntityId> items;
        };
        struct Orientation {
            F32 angle; ///in radians
        };

        IdMap<EntityId, Pos>          pos;
        IdMap<EntityId, Name>         name;
        IdMap<EntityId, Visible>      visible;
        IdMap<EntityId, Item>         item;
        IdMap<EntityId, Container>    container;
        IdMap<EntityId, Orientation>  orientation;
    };
    struct DbgInf {
        struct Shape {
            struct Sphere {
                Vec2F pos;
                F32   rad;
            };
            struct Rect {
                Vec2F pos;
                Vec2F sz;
            };
            struct Line {
                Vec2F beg;
                Vec2F end;
            };
            struct Point {
                Vec2F pos;
            };
            enum Tag : U8 {
                SPHERE,
                RECT,
                LINE,
                POINT,
                TAG_MAX,
            } tag = TAG_MAX;
            union {
                Sphere sphere;
                Rect rect;
                Line line;
                Point point;
            };
        };
        DynArr<Shape> shapes;
    };
    EntityId         player_id;
    EntityComps      entity_comps;
    DbgInf           dbg_inf;
    DynArr<EntityId> entities;
};

struct NetSsSgnl {
    struct Tiles {
        struct Chunk {
            Arr<TileId , CHK_VOL> id;
            BitArr<CHK_VOL>     wall;
        };
        VecMap<ChkPos, Chunk> chunks;
    };
    struct Light {
        struct Chunk {
            Arr<LightLvl, CHK_VOL> light_lvl;
        };
        VecMap<ChkPos, Chunk> chunks;
    };
    struct Msg {
        DynArr<char> contents;
    };
    enum Tag : U8 {
        TILES = 0x00,
        LIGHT = 0x01,
        MSG   = 0x02,
        TAG_MAX,
    } tag = TAG_MAX;

    Tiles tiles;
    Light light;
    Msg   msg;
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
