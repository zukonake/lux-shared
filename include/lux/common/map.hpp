#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/component_wise.hpp>
#undef GLM_ENABLE_EXPERIMENTAL
//
#include <lux/alias/scalar.hpp>
#include <lux/alias/vec_3.hpp>
#include <lux/sign_repr.hpp>

#if SIGN_REPR != SIGN_REPR_TWOS_COMPLEMENT
#   warning "the bitwise coordinates might not work on signed representations" \
            "different than two's complement, testing needed"
#endif

typedef I32 ChkCoord;
typedef U32 ChkIdx;
typedef I32 MapCoord;
typedef Vec3<ChkCoord> ChkPos;
typedef Vec3<MapCoord> MapPos;
typedef Vec3<ChkIdx>   IdxPos;

constexpr Vec3US CHK_SIZE_EXP  = {4, 4, 2};
constexpr Vec3UI CHK_SIZE      = {1 << CHK_SIZE_EXP.x,
                                  1 << CHK_SIZE_EXP.y,
                                  1 << CHK_SIZE_EXP.z};
constexpr SizeT  CHK_VOLUME    = CHK_SIZE.x * CHK_SIZE.y * CHK_SIZE.z;
constexpr Vec3UI CHK_IDX_SIDE  = {0,
                                  CHK_SIZE_EXP.x,
                                  CHK_SIZE_EXP.x + CHK_SIZE_EXP.y};
constexpr Vec3UI CHK_IDX_MASK  = {CHK_SIZE.x - 1,
                                  CHK_SIZE.y - 1,
                                  CHK_SIZE.z - 1};
constexpr Vec3I  CHK_POS_MASK  = {~CHK_IDX_MASK.x,
                                  ~CHK_IDX_MASK.y,
                                  ~CHK_IDX_MASK.z};
constexpr Vec3I  CHK_POS_SHIFT = CHK_SIZE_EXP;

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
    Vec3UI shifted = idx_pos << CHK_IDX_SIDE;
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
