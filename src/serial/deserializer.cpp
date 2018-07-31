#include <cassert>
#include <cstring>
//
#include <lux/net/net_order.hpp>
#include <lux/util/log.hpp>
#include <lux/serial/deserializer.hpp>

namespace serial
{

void Deserializer::set_slice(U8 const *_start, U8 const *_end)
{
    iter = _start;
    end  = _end;
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
    net::net_memcpy((U8 *)&v, out.iter, 2);
    out.iter += 2;
    return out;
}

Deserializer &operator>>(Deserializer &out, U32 &v)
{
    assert(out.get_size() >= 4);
    net::net_memcpy((U8 *)&v, out.iter, 4);
    out.iter += 4;
    return out;
}

Deserializer &operator>>(Deserializer &out, U64 &v)
{
    assert(out.get_size() >= 8);
    net::net_memcpy((U8 *)&v, out.iter, 8);
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

Deserializer &operator>>(Deserializer &out, char &v)
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
