#include <cmath>
//
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/component_wise.hpp>
#undef GLM_ENABLE_EXPERIMENTAL
//
#include <lux/sign_repr.hpp>
#include <lux/common/chunk.hpp>

namespace chunk
{

Pos to_pos(map::Pos const &pos)
{
#if SIGN_REPR == SIGN_REPR_TWOS_COMPLEMENT
    /* when we treat signed as unsigned, the negative values won't round to 0
     */
    Pos rval;
    typedef std::make_unsigned<map::Coord>::type Unsigned;
    rval = (Vec3<Unsigned> const &)pos / (Vec3<Unsigned>)SIZE;
#else
#   warning "using unoptimized chunk::to_pos because of signed representation"
    Pos rval = pos;
    if(pos.x < 0) rval.x -= SIZE.x - 1; //TODO not sure if those work perfectly
    if(pos.y < 0) rval.y -= SIZE.y - 1; //
    if(pos.z < 0) rval.z -= SIZE.z - 1; //
    rval /= SIZE;
#endif
    return rval;
}

Index to_index(map::Pos const &pos)
{
    constexpr Size MULT = {1, SIZE.x, SIZE.x * SIZE.y};
#if SIGN_REPR == SIGN_REPR_TWOS_COMPLEMENT
    /* it's easier if we treat it as unsigned, since we don't really care about
     * the value itself, it will get cut anyway
     */
    typedef std::make_unsigned<map::Coord>::type Unsigned;
    Vec3<Index> rval;
    rval = (Vec3<Unsigned> const &)pos % (Vec3<Index>)SIZE;
#else
#   warning "using unoptimized chunk::to_index because of signed representation"
    map::Pos rval = pos;
    rval %= SIZE;
    if(rval.x < 0) rval.x += SIZE.x;
    if(rval.y < 0) rval.y += SIZE.y;
    if(rval.z < 0) rval.z += SIZE.z;
#endif
    rval *= MULT;
    return glm::compAdd(rval);
}

map::Pos to_map_pos(Pos const &pos, Index const &idx)
{
    /* we use an optimized version if the sizes are powers of 2 */
    //TODO check if works without powers of 2
    //TODO make it work per-coordinate, not for all of them?
    if constexpr((SIZE.x & (SIZE.x - 1)) == 0 &&
                 (SIZE.y & (SIZE.y - 1)) == 0 &&
                 (SIZE.z & (SIZE.z - 1)) == 0)
    {
        /* here we can make use of the fact that every coordinate occupies a
         * certain place in the index
         */
        //TODO vectorize?
        //TODO masks type (U64)?
        constexpr U8  SHIFT_Y = std::log2(SIZE.x);
        constexpr U8  SHIFT_Z = std::log2(SIZE.y) + SHIFT_Y;
        constexpr U64 X_MASK  =  SIZE.x - 1;
        constexpr U64 Y_MASK  = (SIZE.y - 1) << SHIFT_Y;
        constexpr U64 Z_MASK  = (SIZE.z - 1) << SHIFT_Z;
        return (map::Pos)(pos * (Pos)SIZE) +
                map::Pos( idx & X_MASK,
                         (idx & Y_MASK) >> SHIFT_Y,
                         (idx & Z_MASK) >> SHIFT_Z);
    }
    else
    {
        return (map::Pos)(pos * (Pos)SIZE) +
                map::Pos( idx % SIZE.x,
                         (idx / SIZE.x) % SIZE.y,
                          idx / (SIZE.x * SIZE.y));
    }
}

}
