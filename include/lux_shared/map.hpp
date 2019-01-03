#pragma once

#include <lux_shared/common.hpp>

#if LUX_SIGN_REPR != LUX_SIGN_REPR_TWOS_COMPLEMENT
#   warning "the bitwise coordinates might not work on signed representations" \
            "different than two's complement, testing needed"
#endif

typedef I64 ChkCoord;
typedef U16 ChkIdx;
typedef I64 MapCoord;
typedef Vec3<ChkCoord> ChkPos;
typedef Vec3<MapCoord> MapPos;
typedef Vec3<ChkIdx>   IdxPos;

typedef U16 BlockId;
typedef U16 LightLvl;

BlockId constexpr void_block = 0;

///if you need to change the chunk size, change this only
U64 constexpr CHK_SIZE_EXP = 4;

U64 constexpr CHK_SIZE = 1 << CHK_SIZE_EXP;
U64 constexpr CHK_VOL  = CHK_SIZE * CHK_SIZE * CHK_SIZE;
static_assert(CHK_VOL <= 1 << (sizeof(ChkIdx) * 8));

inline ChkPos to_chk_pos(MapPos const &map_pos)
{
    return {(map_pos.x & (I64)~(CHK_SIZE - 1)) >> (I64)CHK_SIZE_EXP,
            (map_pos.y & (I64)~(CHK_SIZE - 1)) >> (I64)CHK_SIZE_EXP,
            (map_pos.z & (I64)~(CHK_SIZE - 1)) >> (I64)CHK_SIZE_EXP};
}

inline IdxPos to_idx_pos(MapPos const &map_pos)
{
    return {map_pos.x & (CHK_SIZE - 1),
            map_pos.y & (CHK_SIZE - 1),
            map_pos.z & (CHK_SIZE - 1)};
}

inline IdxPos to_idx_pos(ChkIdx const &chk_idx)
{
    return { chk_idx &  (CHK_SIZE - 1),
            (chk_idx & ((CHK_SIZE - 1) <<  CHK_SIZE_EXP     )) >>  CHK_SIZE_EXP,
            (chk_idx & ((CHK_SIZE - 1) << (CHK_SIZE_EXP * 2))) >> (CHK_SIZE_EXP * 2)};
}

inline ChkIdx to_chk_idx(IdxPos const &idx_pos)
{
    return idx_pos.x | (idx_pos.y << CHK_SIZE_EXP) | (idx_pos.z << (CHK_SIZE_EXP * 2));
}

inline ChkIdx to_chk_idx(MapPos const &map_pos)
{
    return to_chk_idx(to_idx_pos(map_pos));
}

inline MapPos to_map_pos(ChkPos const &chk_pos, IdxPos const &idx_pos)
{
    return {(chk_pos.x << (ChkCoord)CHK_SIZE_EXP) | idx_pos.x,
            (chk_pos.y << (ChkCoord)CHK_SIZE_EXP) | idx_pos.y,
            (chk_pos.z << (ChkCoord)CHK_SIZE_EXP) | idx_pos.z};
}

inline MapPos to_map_pos(ChkPos const &chk_pos, ChkIdx const &chk_idx)
{
    return to_map_pos(chk_pos, to_idx_pos(chk_idx));
}
