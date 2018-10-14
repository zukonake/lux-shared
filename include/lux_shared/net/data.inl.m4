divert(-1)
define(`quote', `ifelse(`$#', `0', `', ``$*'')')
define(`dquote', ``$@'')
define(`dquote_elt', `ifelse(`$#', `0', `', `$#', `1', ```$1''',
                             ```$1'',$0(shift($@))')')

define(`foreach', `pushdef(`$1')_foreach($@)popdef(`$1')')
define(`_arg1', `$1')
define(`_foreach', `ifelse(quote($2), `', `',
    `define(`$1', `_arg1($2)')$3`'$0(`$1', `shift($2)', `$3')')')

define(`m4_get_members', `shift(shift($@))')

define(`m4_lux_net_data', `dnl
ifelse(`$2', `static', `dnl
template<> struct HasStaticSz<$1> { bool static constexpr val = true; };
LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end, $1* val) {
    if(buff_sz_at_least(sizeof($1), *buff, buff_end) != LUX_OK) {
        return LUX_FAIL;
    }
foreach(`x', `m4_get_members($@)', `    (void)deserialize(buff, buff_end, &val->x);
')
    return LUX_OK;
}', `
SizeT get_real_sz($1 const& val) {
    return foreach(`x', `m4_get_members($@)', `get_real_sz(val.x) +
           ')0;
}

LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end, $1* val) {
    if(foreach(`x', `m4_get_members($@)',
`deserialize(buff, buff_end, &val->x) != LUX_OK ||
       ')false) {
        return LUX_FAIL;
    }
    return LUX_OK;
}
')

void serialize(U8** buff, $1 const& val) {
foreach(`x', `m4_get_members($@)', `    serialize(buff, val.x);
')}
')
divert(0)dnl
#include <lux_shared/net/serial.hpp>
#include <lux_shared/net/data.hpp>

m4_lux_net_data(EntityComps::Shape, static, rad)
m4_lux_net_data(EntityComps::Visible, static, texture_id)
m4_lux_net_data(EntityComps::Item, static, weight)
m4_lux_net_data(EntityComps::Destructible, static, dur, dur_max)
m4_lux_net_data(EntityComps::Animated, static, time, time_max)
m4_lux_net_data(EntityComps, dynamic,
    pos, vel, shape, visible, item, destructible, animated)

m4_lux_net_data(NetSsInit, static, name, tick_rate)
m4_lux_net_data(NetSsTick, dynamic, player_id, comps)
m4_lux_net_data(NetSsSgnl::MapLoad::Chunk, static, voxels, light_lvls)
m4_lux_net_data(NetSsSgnl::MapLoad, dynamic, chunks)
m4_lux_net_data(NetSsSgnl::LightUpdate::Chunk, static, light_lvls)
m4_lux_net_data(NetSsSgnl::LightUpdate, dynamic, chunks)
m4_lux_net_data(NetCsSgnl::MapRequest, dynamic, requests)
m4_lux_net_data(NetCsSgnl::Command, dynamic, contents)
m4_lux_net_data(NetCsInit, static,
    net_ver.major, net_ver.minor, net_ver.patch, name)
m4_lux_net_data(NetCsTick, static, player_dir)

SizeT get_real_sz(NetSsSgnl const& sgnl) {
    SizeT sz = sizeof(NetSsSgnl::Header);
    switch(sgnl.header) {
        case NetSsSgnl::MAP_LOAD: {
            sz += get_real_sz(sgnl.map_load);
        } break;
        case NetSsSgnl::LIGHT_UPDATE: {
            sz += get_real_sz(sgnl.light_update);
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
            if(deserialize(buff, buff_end, &sgnl->map_load) != LUX_OK) {
                return LUX_FAIL;
            }
        } break;
        case NetSsSgnl::LIGHT_UPDATE: {
            if(deserialize(buff, buff_end, &sgnl->light_update) != LUX_OK) {
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
            serialize(buff, sgnl.map_load);
        } break;
        case NetSsSgnl::LIGHT_UPDATE: {
            serialize(buff, sgnl.light_update);
        } break;
        case NetSsSgnl::MSG: {
            serialize(buff, sgnl.msg.contents);
        } break;
        default: LUX_UNREACHABLE();
    }
}

SizeT get_real_sz(NetCsSgnl const& sgnl) {
    SizeT sz = sizeof(NetCsSgnl::Header);
    switch(sgnl.header) {
        case NetCsSgnl::MAP_REQUEST: {
            sz += get_real_sz(sgnl.map_request);
        } break;
        case NetCsSgnl::COMMAND: {
            sz += get_real_sz(sgnl.command);
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
            if(deserialize(buff, buff_end, &sgnl->map_request) != LUX_OK) {
                return LUX_FAIL;
            }
        } break;
        case NetCsSgnl::COMMAND: {
            if(deserialize(buff, buff_end, &sgnl->command) != LUX_OK) {
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
            serialize(buff, sgnl.map_request);
        } break;
        case NetCsSgnl::COMMAND: {
            serialize(buff, sgnl.command);
        } break;
        default: LUX_UNREACHABLE();
    }
}
