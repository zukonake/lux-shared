#pragma once

#include <lux_shared/common.hpp>

#if LUX_SIGN_REPR != LUX_SIGN_REPR_TWOS_COMPLEMENT
#   warning "the bitwise coordinates might not work on signed representations" \
            "different than two's complement, testing needed"
#endif

//TODO static asserts

typedef I64 ChkCoord;
typedef U16 ChkIdx;
typedef I64 MapCoord;
typedef Vec3<ChkCoord> ChkPos;
typedef Vec3<MapCoord> MapPos;
typedef Vec3<ChkIdx>   IdxPos;

typedef U16 VoxelId;
typedef U16 LightLvl;

///if you need to change the chunk size, change this only
Vec3U constexpr CHK_SIZE_EXP  = {3, 3, 2};

Vec3U constexpr CHK_SIZE      = {1 << CHK_SIZE_EXP.x,
                                 1 << CHK_SIZE_EXP.y,
                                 1 << CHK_SIZE_EXP.z};
SizeT constexpr CHK_VOL       = CHK_SIZE.x * CHK_SIZE.y * CHK_SIZE.z;
static_assert(CHK_VOL <= 1 << (sizeof(ChkIdx) * 8));

Vec3<U16> constexpr CHK_IDX_SIDE  = {0,
                                     CHK_SIZE_EXP.x,
                                     CHK_SIZE_EXP.x + CHK_SIZE_EXP.y};
Vec3<U16> constexpr CHK_IDX_MASK  = {CHK_SIZE.x - 1,
                                     CHK_SIZE.y - 1,
                                     CHK_SIZE.z - 1};
Vec3<I64> constexpr CHK_POS_MASK  = {~CHK_IDX_MASK.x,
                                     ~CHK_IDX_MASK.y,
                                     ~CHK_IDX_MASK.z};
Vec3<U16> constexpr CHK_IDX_OFF   = {1,
                                     CHK_SIZE.x,
                                     CHK_SIZE.x + CHK_SIZE.y};
Vec3<I64> constexpr CHK_POS_SHIFT = CHK_SIZE_EXP;

inline ChkPos to_chk_pos(MapPos const &map_pos)
{
    return (map_pos & CHK_POS_MASK) >> CHK_POS_SHIFT;
}

inline IdxPos to_idx_pos(MapPos const &map_pos)
{
    return (IdxPos const &)map_pos & CHK_IDX_MASK;
}

inline IdxPos to_idx_pos(ChkIdx const &chk_idx)
{
    return (chk_idx & (CHK_IDX_MASK << CHK_IDX_SIDE)) >> CHK_IDX_SIDE;
}

inline ChkIdx to_chk_idx(IdxPos const &idx_pos)
{
    Vec3U shifted = idx_pos << CHK_IDX_SIDE;
    return shifted.x | shifted.y | shifted.z;
}

inline ChkIdx to_chk_idx(MapPos const &map_pos)
{
    return to_chk_idx(to_idx_pos(map_pos));
}

inline MapPos to_map_pos(ChkPos const &chk_pos, IdxPos const &idx_pos)
{
    return (chk_pos << CHK_POS_SHIFT) | (MapPos const &)idx_pos;
}

inline MapPos to_map_pos(ChkPos const &chk_pos, ChkIdx const &chk_idx)
{
    return (chk_pos << CHK_POS_SHIFT) | (MapPos const &)to_idx_pos(chk_idx);
}
