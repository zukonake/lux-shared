#include <cmath>
//
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/component_wise.hpp>
#undef  GLM_ENABLE_EXPERIMENTAL
//
#include <lux/common/map.hpp>

void build_chunk_mesh(
    ChkPos const &pos,
    std::function<bool(MapPos const &, MapPos const &)> has_face,
    std::function<void(Vec3<U32> const &base, U32 plane, ChkIdx chk_idx,
                       Vec3<U32> const &f_side,
                       Vec3<U32> const &s_side)> add_quad)
    //TODO this is probably slow as fuck
{
    constexpr MapPos offsets[3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    bool solid_map[3][CHK_VOLUME];
    MapPos base_pos = to_map_pos(pos, 0);
    for(U32 i = 0; i < CHK_VOLUME; ++i) {
        IdxPos i_pos = to_idx_pos(i);
        MapPos m_pos = base_pos + (MapPos)i_pos;
        for(U32 s = 0; s < 3; ++s) {
            solid_map[s][i] = has_face(m_pos, m_pos + offsets[s]);
        }
    }
    constexpr Vec3<U32> idx_offsets = {1, CHK_SIZE.x, CHK_SIZE.x * CHK_SIZE.y};
    for(U32 s = 0; s < 3; ++s) {
        /* two axes we use to scan the plane for quads */
        Vec3<U32> f_axis(s == 2, s == 0, s == 1);
        Vec3<U32> s_axis(s == 1, s == 2, s == 0);

        /* used to quickly increment chunk index by one on respective axis */
        U32 f_idx_side = compMax(idx_offsets * f_axis);
        U32 s_idx_side = compMax(idx_offsets * s_axis);

        /* max sizes for axes */
        U32 f_size = compMax(f_axis * CHK_SIZE);
        U32 s_size = compMax(s_axis * CHK_SIZE);
        for(U32 i = 0; i < CHK_VOLUME; ++i) {
            IdxPos i_pos = to_idx_pos(i);

            if(solid_map[s][i]) {
                /* starting coords for scan */
                U32 f_co = compMax(f_axis * i_pos);
                U32 s_co = compMax(s_axis * i_pos);

                /* get first axis length scan until block without a face is hit
                 * or we exceed axis size */
                U32 f_d_i = 0;
                for(; f_co + f_d_i < f_size; ++f_d_i) {
                    if(!solid_map[s][i + f_d_i * f_idx_side]) break;
                }

                /* those will be the resulting quad's sides
                 * second axis is set to illegal value, because it has to be
                 * overriden using min() */
                U32 f_d = f_d_i;
                U32 s_d = s_size;

                /* we find length of the second axis */
                for(U32 f_i = 0; f_i < f_d; ++f_i) {
                    U32 s_d_i = 0;
                    for(; s_co + s_d_i < s_size; ++s_d_i) {
                        if(!solid_map[s][i + f_i   * f_idx_side +
                                             s_d_i * s_idx_side]) break;
                    }
                    /* we cannot exceed the smallest side length so far,
                     * otherwise we won't get a rectangle */
                    s_d = std::min(s_d, s_d_i);
                }

                /* now that we have the quad's sides, we set the faces to false,
                 * so that they won't be used to create another quad,
                 * that would result in overlapping quads */
                for(U32 f_i = 0; f_i < f_d; ++f_i) {
                    for(U32 s_i = 0; s_i < s_d; ++s_i) {
                        solid_map[s][i + f_i * f_idx_side +
                                         s_i * s_idx_side] = false;
                    }
                }

                add_quad((MapPos)i_pos + offsets[s], s, i,
                         f_d * f_axis, s_d * s_axis);
            }
        }
    }
}

