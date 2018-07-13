#pragma once

#include <alias/int.hpp>
#include <linear/point_2d.hpp>
#include <net/serializer.hpp>
#include <net/deserializer.hpp>

namespace net
{

//TODO generally much this struct should be replaced by a hash of a ID,
//     this struct represents a TileType, and those will be held in the Database
//     both client and server side, so there is no need to transfer it all,
//     same applies to future "*Type" structs
#pragma pack(push, 1)
struct TileState
{
    typedef linear::Point2d<U8> TexPos;
    enum Shape : U8
    {
        EMPTY,
        FLOOR,
        WALL
    };

    Shape shape;
    TexPos tex_pos;
};
#pragma pack(pop)

template<>
inline void Serializer::push<TileState>(TileState const &val)
{
    push<U8>((U8)val.shape);
    push<U8>(val.tex_pos.x);
    push<U8>(val.tex_pos.y);
}

template<>
inline void Deserializer::pop<TileState>(TileState &val)
{
    pop<U8>((U8 &)val.shape);
    pop<U8>(val.tex_pos.x);
    pop<U8>(val.tex_pos.y);
}

}
