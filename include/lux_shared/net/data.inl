#include <lux_shared/net/serial.hpp>
#include <lux_shared/net/data.hpp>

LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end,
                         EntityComps::Shape* shape) {
    if(buff_sz_at_least(sizeof(EntityComps::Shape),
                        *buff, buff_end) != LUX_OK) {
        return LUX_FAIL;
    }
    (void)deserialize(buff, buff_end, &shape->rad);
    return LUX_OK;
}

void serialize(U8** buff, EntityComps::Shape const& shape) {
    serialize(buff, shape.rad);
}

LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end,
                         EntityComps::Visible* visible) {
    if(buff_sz_at_least(sizeof(EntityComps::Visible),
                        *buff, buff_end) != LUX_OK) {
        return LUX_FAIL;
    }
    (void)deserialize(buff, buff_end, &visible->texture_id);
    return LUX_OK;
}

void serialize(U8** buff, EntityComps::Visible const& visible) {
    serialize(buff, visible.texture_id);
}

LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end,
                         EntityComps::Item* item) {
    if(buff_sz_at_least(sizeof(EntityComps::Item),
                        *buff, buff_end) != LUX_OK) {
        return LUX_FAIL;
    }
    (void)deserialize(buff, buff_end, &item->weight);
    return LUX_OK;
}

void serialize(U8** buff, EntityComps::Item const& item) {
    serialize(buff, item.weight);
}

LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end,
                         EntityComps::Destructible* destructible) {
    if(buff_sz_at_least(sizeof(EntityComps::Destructible),
                        *buff, buff_end) != LUX_OK) {
        return LUX_FAIL;
    }
    (void)deserialize(buff, buff_end, &destructible->dur);
    (void)deserialize(buff, buff_end, &destructible->dur_max);
    return LUX_OK;
}

void serialize(U8** buff, EntityComps::Destructible const& destructible) {
    serialize(buff, destructible.dur);
    serialize(buff, destructible.dur_max);
}

LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end,
                         EntityComps::Animated* animated) {
    if(buff_sz_at_least(sizeof(EntityComps::Animated),
                        *buff, buff_end) != LUX_OK) {
        return LUX_FAIL;
    }
    (void)deserialize(buff, buff_end, &animated->time);
    (void)deserialize(buff, buff_end, &animated->time_max);
    return LUX_OK;
}

void serialize(U8** buff, EntityComps::Animated const& animated) {
    serialize(buff, animated.time);
    serialize(buff, animated.time_max);
}

SizeT get_real_sz(EntityComps const& comps) {
    return get_real_sz(comps.pos) +
           get_real_sz(comps.vel) +
           get_real_sz(comps.shape) +
           get_real_sz(comps.visible) +
           get_real_sz(comps.item) +
           get_real_sz(comps.destructible) +
           get_real_sz(comps.animated);
}

LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end,
                         EntityComps* comps) {
    if(deserialize(buff, buff_end, &comps->pos) != LUX_OK ||
       deserialize(buff, buff_end, &comps->vel) != LUX_OK ||
       deserialize(buff, buff_end, &comps->shape) != LUX_OK ||
       deserialize(buff, buff_end, &comps->visible) != LUX_OK ||
       deserialize(buff, buff_end, &comps->item) != LUX_OK ||
       deserialize(buff, buff_end, &comps->destructible) != LUX_OK ||
       deserialize(buff, buff_end, &comps->animated)) {
        return LUX_FAIL;
    }
    return LUX_OK;
}

void serialize(U8** buff, EntityComps const& comps) {
    serialize(buff, comps.pos);
    serialize(buff, comps.vel);
    serialize(buff, comps.shape);
    serialize(buff, comps.visible);
    serialize(buff, comps.item);
    serialize(buff, comps.destructible);
    serialize(buff, comps.animated);
}

LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end, NetSsInit* init) {
    if(buff_sz_at_least(sizeof(NetSsInit), *buff, buff_end) != LUX_OK) {
        return LUX_FAIL;
    }
    (void)deserialize(buff, buff_end, &init->name);
    (void)deserialize(buff, buff_end, &init->tick_rate);
    return LUX_OK;
}

void serialize(U8** buff, NetSsInit const& init) {
    serialize(buff, init.name);
    serialize(buff, init.tick_rate);
}

SizeT get_real_sz(NetSsTick const& tick) {
    return get_real_sz(tick.player_id) + get_real_sz(tick.comps);
}

LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end, NetSsTick* tick) {
    if(deserialize(buff, buff_end, &tick->player_id) != LUX_OK ||
       deserialize(buff, buff_end, &tick->comps) != LUX_OK) {
        return LUX_FAIL;
    }
    return LUX_OK;
}

void serialize(U8** buff, NetSsTick const& tick) {
    serialize(buff, tick.player_id);
    serialize(buff, tick.comps);
}

LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end,
                         NetSsSgnl::MapLoad::Chunk* chunk) {
    if(buff_sz_at_least(sizeof(NetSsSgnl::MapLoad::Chunk),
                        *buff, buff_end) != LUX_OK) {
        return LUX_FAIL;
    }
    (void)deserialize(buff, buff_end, &chunk->voxels);
    (void)deserialize(buff, buff_end, &chunk->light_lvls);
    return LUX_OK;
}

void serialize(U8** buff, NetSsSgnl::MapLoad::Chunk const& chunk) {
    serialize(buff, chunk.voxels);
    serialize(buff, chunk.light_lvls);
}

LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end,
                         NetSsSgnl::LightUpdate::Chunk* chunk) {
    if(buff_sz_at_least(sizeof(NetSsSgnl::LightUpdate::Chunk),
                        *buff, buff_end) != LUX_OK) {
        return LUX_FAIL;
    }
    (void)deserialize(buff, buff_end, &chunk->light_lvls);
    return LUX_OK;
}

void serialize(U8** buff, NetSsSgnl::LightUpdate::Chunk const& chunk) {
    serialize(buff, chunk.light_lvls);
}

SizeT get_real_sz(NetSsSgnl const& sgnl) {
    SizeT sz = sizeof(NetSsSgnl::Header);
    switch(sgnl.header) {
        case NetSsSgnl::MAP_LOAD: {
            sz += get_real_sz(sgnl.map_load.chunks);
        } break;
        case NetSsSgnl::LIGHT_UPDATE: {
            sz += get_real_sz(sgnl.light_update.chunks);
        } break;
        case NetSsSgnl::MSG: {
            sz += get_real_sz(sgnl.msg.contents);
        } break;
        default: LUX_UNREACHABLE();
    }
    return sz;
}

LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end, NetSsSgnl* sgnl) {
    if(deserialize(buff, buff_end, (U8*)&sgnl->header) != LUX_OK) {
        return LUX_FAIL;
    }
    switch(sgnl->header) {
        case NetSsSgnl::MAP_LOAD: {
            if(deserialize(buff, buff_end, &sgnl->map_load.chunks) != LUX_OK) {
                return LUX_FAIL;
            }
        } break;
        case NetSsSgnl::LIGHT_UPDATE: {
            if(deserialize(buff, buff_end,
                           &sgnl->light_update.chunks) != LUX_OK) {
                return LUX_FAIL;
            }
        } break;
        case NetSsSgnl::MSG: {
            if(deserialize(buff, buff_end, &sgnl->msg.contents) != LUX_OK) {
                return LUX_FAIL;
            }
        } break;
        default: {
            LUX_LOG("unexpected signal header %u", sgnl->header);
            return LUX_FAIL;
        } break;
    }
    return LUX_OK;
}

void serialize(U8** buff, NetSsSgnl const& sgnl) {
    serialize(buff, (U8 const&)sgnl.header);
    switch(sgnl.header) {
        case NetSsSgnl::MAP_LOAD: {
            serialize(buff, sgnl.map_load.chunks);
        } break;
        case NetSsSgnl::LIGHT_UPDATE: {
            serialize(buff, sgnl.light_update.chunks);
        } break;
        case NetSsSgnl::MSG: {
            serialize(buff, sgnl.msg.contents);
        } break;
        default: LUX_UNREACHABLE();
    }
}

LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end, NetCsTick* tick) {
    if(buff_sz_at_least(sizeof(NetCsTick), *buff, buff_end) != LUX_OK) {
        return LUX_FAIL;
    }
    (void)deserialize(buff, buff_end, &tick->player_dir);
    return LUX_OK;
}

void serialize(U8** buff, NetCsTick const& tick) {
    serialize(buff, tick.player_dir);
}

LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end, NetCsInit* init) {
    if(buff_sz_at_least(sizeof(NetCsInit), *buff, buff_end) != LUX_OK) {
        return LUX_FAIL;
    }
    (void)deserialize(buff, buff_end, &init->net_ver.major);
    (void)deserialize(buff, buff_end, &init->net_ver.minor);
    (void)deserialize(buff, buff_end, &init->net_ver.patch);
    (void)deserialize(buff, buff_end, &init->name);
    return LUX_OK;
}

void serialize(U8** buff, NetCsInit const& init) {
    serialize(buff, init.net_ver.major);
    serialize(buff, init.net_ver.minor);
    serialize(buff, init.net_ver.patch);
    serialize(buff, init.name);
}

SizeT get_real_sz(NetCsSgnl const& sgnl) {
    SizeT sz = sizeof(NetCsSgnl::Header);
    switch(sgnl.header) {
        case NetCsSgnl::MAP_REQUEST: {
            sz += get_real_sz(sgnl.map_request.requests);
        } break;
        case NetCsSgnl::COMMAND: {
            sz += get_real_sz(sgnl.command.contents);
        } break;
        default: LUX_UNREACHABLE();
    }
    return sz;
}

LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end, NetCsSgnl* sgnl) {
    if(deserialize(buff, buff_end, (U8*)&sgnl->header) != LUX_OK) {
        return LUX_FAIL;
    }
    switch(sgnl->header) {
        case NetCsSgnl::MAP_REQUEST: {
            if(deserialize(buff, buff_end,
                           &sgnl->map_request.requests) != LUX_OK) {
                return LUX_FAIL;
            }
        } break;
        case NetCsSgnl::COMMAND: {
            if(deserialize(buff, buff_end, &sgnl->command.contents) != LUX_OK) {
                return LUX_FAIL;
            }
        } break;
        default: {
            LUX_LOG("unexpected signal header %u", sgnl->header);
            return LUX_FAIL;
        } break;
    }
    return LUX_OK;
}

void serialize(U8** buff, NetCsSgnl const& sgnl) {
    serialize(buff, (U8 const&)sgnl.header);
    switch(sgnl.header) {
        case NetCsSgnl::MAP_REQUEST: {
            serialize(buff, sgnl.map_request.requests);
        } break;
        case NetCsSgnl::COMMAND: {
            serialize(buff, sgnl.command.contents);
        } break;
        default: LUX_UNREACHABLE();
    }
}
