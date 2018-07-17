#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/linear/vec_2.hpp>
#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>

namespace net
{

//TODO generally much this struct should be replaced by a hash of a ID,
//     this struct represents a TileType, and those will be held in the Database
//     both client and server side, so there is no need to transfer it all,
//     same applies to future "*Type" structs
#pragma pack(push, 1)
struct TileState
{
    typedef linear::Vec2<U8> TexPos;
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

inline Serializer &operator<<(Serializer &in, TileState const &v)
{
    in << (U8 const &)v.shape;
    in << v.tex_pos;
    return in;
}

inline Deserializer &operator>>(Deserializer &out, TileState &v)
{
    out >> (U8 &)v.shape;
    out >> v.tex_pos;
    return out;
}

}
