#pragma once

#include <alias/int.hpp>
#include <alias/vector.hpp>
#include <linear/size_2d.hpp>

namespace net
{

struct ClientData
{
    linear::Size2d<U16> view_size; //in tiles

    static void   serialize(ClientData const &client_data, Vector<U8>       &bytes);
    static void deserialize(ClientData       &client_data, Vector<U8> const &bytes);
};

}
