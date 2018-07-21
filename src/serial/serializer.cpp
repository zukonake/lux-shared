#include <cassert>
#include <cstring>
//
#include <lux/net/net_order.hpp>
#include <lux/util/log.hpp>
#include <lux/serial/serializer.hpp>

namespace serial
{

Vector<U8> const &Serializer::get() const
{
    return storage;
}

void Serializer::clear()
{
    storage.clear();
}

Serializer &operator<<(Serializer &in, U8 const &v)
{
    in.storage.emplace_back(v);
    return in;
}

Serializer &operator<<(Serializer &in, U16 const &v)
{
    U16 temp = net::net_order<U16>(v);
    in.storage.resize(in.storage.size() + 2);
    in.storage.insert(in.storage.end() - 2, (U8 *)&temp, (U8 *)&temp + 1);
    return in;
}

Serializer &operator<<(Serializer &in, U32 const &v)
{
    U32 temp = net::net_order<U32>(v);
    in.storage.resize(in.storage.size() + 4);
    in.storage.insert(in.storage.end() - 4, (U8 *)&temp, (U8 *)&temp + 3);
    return in;
}

Serializer &operator<<(Serializer &in, U64 const &v)
{
    U64 temp = net::net_order<U64>(v);
    in.storage.resize(in.storage.size() + 8);
    in.storage.insert(in.storage.end() - 8, (U8 *)&temp, (U8 *)&temp + 7);
    return in;
}

Serializer &operator<<(Serializer &in, I8 const &v)
{
    in << *((U8 const *)&v);
    return in;
}

Serializer &operator<<(Serializer &in, I16 const &v)
{
    in << *((U16 const *)&v);
    return in;
}

Serializer &operator<<(Serializer &in, I32 const &v)
{
    in << *((U32 const *)&v);
    return in;
}

Serializer &operator<<(Serializer &in, I64 const &v)
{
    in << *((U64 const *)&v);
    return in;
}

Serializer &operator<<(Serializer &in, bool const &v)
{
    in << *((U8 const *)&v);
    return in;
}

Serializer &operator<<(Serializer &in, F32 const &v)
{
    in << *((U32 const *)&v);
    return in;
}

Serializer &operator<<(Serializer &in, F64 const &v)
{
    in << *((U64 const *)&v);
    return in;
}

}
