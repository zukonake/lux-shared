#pragma once

#include <alias/int.hpp>
#include <alias/vector.hpp>
#include <linear/size_2d.hpp>
#include <linear/vector_2d.hpp>
#include <net/serialize.hpp>
#include <net/deserialize.hpp>

namespace net
{

#pragma pack(push, 1)
struct ClientData
{
    linear::Size2d<U16>     view_size;    //in tiles
    linear::Vector2d<float> character_dir;
    bool is_moving;
};
#pragma pack(pop)

//TODO add asserts so that member types can be changed safely, same in ServerData
template<>
inline void serialize<ClientData>(Vector<U8> &bytes, ClientData const &client_data)
{
    static_assert(sizeof(U32) == sizeof(float));
    assert(bytes.size() == 0);
    bytes.reserve(sizeof(ClientData));
    serialize<U16>(bytes, client_data.view_size.x);
    serialize<U16>(bytes, client_data.view_size.y);
    serialize<U32>(bytes, (U32)client_data.character_dir.x);
    serialize<U32>(bytes, (U32)client_data.character_dir.y);
    serialize<bool>(bytes, client_data.is_moving);
}

template<>
inline void deserialize<ClientData>(Vector<U8> &bytes, ClientData &client_data)
{
    static_assert(sizeof(U32) == sizeof(float));
    assert(bytes.size() == sizeof(ClientData));
    deserialize<U16>(bytes, client_data.view_size.x);
    deserialize<U16>(bytes, client_data.view_size.y);
    deserialize<U32>(bytes, (U32 &)client_data.character_dir.x);
    deserialize<U32>(bytes, (U32 &)client_data.character_dir.y);
    deserialize<bool>(bytes, client_data.is_moving);
    assert(bytes.size() == 0);
}

}
