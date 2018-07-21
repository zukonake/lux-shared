#include <cassert>
#include <cstring>
//
#include <lux/net/net_order.hpp>
#include <lux/util/log.hpp>
#include <lux/serial/deserializer.hpp>

namespace serial
{

void Deserializer::set_slice(U8 const *start, U8 const *end)
{
    this->iter = start;
    this->end  = end;
}

Deserializer &operator>>(Deserializer &out, U8 &v)
{
    assert(out.get_size() >= 1);
    v = *out.iter;
    out.iter++;
    return out;
}

Deserializer &operator>>(Deserializer &out, U16 &v)
{
    assert(out.get_size() >= 2);
    std::memcpy((U8 *)&v, out.iter, 2);
    v = net::net_order<U16>(v);
    out.iter += 2;
    return out;
}

Deserializer &operator>>(Deserializer &out, U32 &v)
{
    assert(out.get_size() >= 4);
    std::memcpy((U8 *)&v, out.iter, 4);
    v = net::net_order<U32>(v);
    out.iter += 4;
    return out;
}

Deserializer &operator>>(Deserializer &out, U64 &v)
{
    assert(out.get_size() >= 8);
    std::memcpy((U8 *)&v, out.iter, 8);
    v = net::net_order<U64>(v);
    out.iter += 8;
    return out;
}

Deserializer &operator>>(Deserializer &out, I8 &v)
{
    out >> *((U8 *)&v);
    return out;
}

Deserializer &operator>>(Deserializer &out, I16 &v)
{
    out >> *((U16 *)&v);
    return out;
}

Deserializer &operator>>(Deserializer &out, I32 &v)
{
    out >> *((U32 *)&v);
    return out;
}

Deserializer &operator>>(Deserializer &out, I64 &v)
{
    out >> *((U64 *)&v);
    return out;
}

Deserializer &operator>>(Deserializer &out, bool &v)
{
    out >> *((U8 *)&v);
    return out;
}

Deserializer &operator>>(Deserializer &out, F32 &v)
{
    out >> *((U32 *)&v);
    return out;
}

Deserializer &operator>>(Deserializer &out, F64 &v)
{
    out >> *((U64 *)&v);
    return out;
}

}
