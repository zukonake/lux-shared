#pragma once

#include <alias/int.hpp>
#include <alias/vector.hpp>
#include <linear/size_2d.hpp>
#include <linear/vector_2d.hpp>
#include <net/serializer.hpp>
#include <net/deserializer.hpp>

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

template<>
inline void Serializer::push<ClientData>(ClientData const &client_data)
{
    static_assert(sizeof(U32) == sizeof(float));
    push<U16>(client_data.view_size.x);
    push<U16>(client_data.view_size.y);
    push<U32>(*(U32 const *)(&client_data.character_dir.x));
    push<U32>(*(U32 const *)(&client_data.character_dir.y));
    push<bool>(client_data.is_moving);
}

template<>
inline void Deserializer::pop<ClientData>(ClientData &client_data)
{
    static_assert(sizeof(U32) == sizeof(float));
    assert(get_size() >= sizeof(ClientData));
    pop<U16>(client_data.view_size.x);
    pop<U16>(client_data.view_size.y);
    pop<U32>((U32 &)client_data.character_dir.x);
    pop<U32>((U32 &)client_data.character_dir.y);
    pop<bool>(client_data.is_moving);
}

}
