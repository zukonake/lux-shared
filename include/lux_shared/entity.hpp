#pragma once

#include <lux_shared/common.hpp>

typedef Vec3<F32> EntityVec;
typedef U32 EntityHandle;

struct EntityComps {
    typedef EntityVec Pos;
    typedef EntityVec Vel;
    struct Shape {
        F32 rad;
    };
    struct Visible {
        U32 texture_id;
    };
    struct Item {
        F32 weight;
    };
    struct Destructible {
        F32 dur;
        F32 dur_max;
    };
    struct Animated {
        F32 time;
        F32 time_max;
    };

    HashTable<EntityHandle, Pos>          pos;
    HashTable<EntityHandle, Vel>          vel;
    HashTable<EntityHandle, Shape>        shape;
    HashTable<EntityHandle, Visible>      visible;
    HashTable<EntityHandle, Item>         item;
    HashTable<EntityHandle, Destructible> destructible;
    HashTable<EntityHandle, Animated>     animated;
};

