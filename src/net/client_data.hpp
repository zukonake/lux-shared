#pragma once

#include <alias/scalar.hpp>
#include <alias/vector.hpp>
#include <linear/vec_2.hpp>
#include <net/serializer.hpp>
#include <net/deserializer.hpp>

namespace net
{

#pragma pack(push, 1)
struct ClientData
{
    linear::Vec2<U16>     view_size;    //in tiles
    linear::Vec2<float> character_dir;
    bool is_moving;
};
#pragma pack(pop)

inline Serializer &operator<<(Serializer &in, ClientData const &v)
{
    in << v.view_size;
    in << v.character_dir;
    in << v.is_moving;
    return in;
}

inline Deserializer &operator>>(Deserializer &out, ClientData &v)
{
    out >> v.view_size;
    out >> v.character_dir;
    out >> v.is_moving;
    return out;
}

}
