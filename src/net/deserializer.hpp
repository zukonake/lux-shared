#pragma once

#include <cassert>
#include <cstring>
//
#include <alias/scalar.hpp>
#include <net/net_order.hpp>

namespace net
{

class Deserializer
{
    public:
    struct Array
    {
        U8   *val;
        SizeT len;
    };

    Deserializer(U8 const *start, U8 const *end) :
        iter(start),
        end(end)
    { }
    ~Deserializer() = default;

    friend Deserializer &operator>>(Deserializer &out, U8    &v);
    friend Deserializer &operator>>(Deserializer &out, U16   &v);
    friend Deserializer &operator>>(Deserializer &out, U32   &v);
    friend Deserializer &operator>>(Deserializer &out, U64   &v);
    friend Deserializer &operator>>(Deserializer &out, Array &v);

    SizeT get_size() const { return (SizeT)(end - iter); }

    private:
    U8 const *iter;
    U8 const *end;
};

inline Deserializer &operator>>(Deserializer &out, U8 &v)
{
    assert(out.get_size() >= 1);
    v = *out.iter;
    out.iter++;
    return out;
}

inline Deserializer &operator>>(Deserializer &out, U16 &v)
{
    assert(out.get_size() >= 2);
    std::memcpy((U8 *)&v, out.iter, 2);
    v = net_order<U16>(v);
    out.iter += 2;
    return out;
}

inline Deserializer &operator>>(Deserializer &out, U32 &v)
{
    assert(out.get_size() >= 4);
    std::memcpy((U8 *)&v, out.iter, 4);
    v = net_order<U32>(v);
    out.iter += 4;
    return out;
}

inline Deserializer &operator>>(Deserializer &out, U64 &v)
{
    assert(out.get_size() >= 8);
    std::memcpy((U8 *)&v, out.iter, 8);
    v = net_order<U64>(v);
    out.iter += 8;
    return out;
}

inline Deserializer &operator>>(Deserializer &out, Deserializer::Array &v)
{
    assert(out.get_size() >= v.len);
    std::memcpy(v.val, out.iter, v.len);
    out.iter += v.len;
    return out;
}

inline Deserializer &operator>>(Deserializer &out, I8 &v)
{
    out >> *((U8 *)&v);
    return out;
}

inline Deserializer &operator>>(Deserializer &out, I16 &v)
{
    out >> *((U16 *)&v);
    return out;
}

inline Deserializer &operator>>(Deserializer &out, I32 &v)
{
    out >> *((U32 *)&v);
    return out;
}

inline Deserializer &operator>>(Deserializer &out, I64 &v)
{
    out >> *((U64 *)&v);
    return out;
}

inline Deserializer &operator>>(Deserializer &out, bool &v)
{
    out >> *((U8 *)&v);
    return out;
}

inline Deserializer &operator>>(Deserializer &out, F32 &v)
{
    out >> *((U32 *)&v);
    return out;
}

inline Deserializer &operator>>(Deserializer &out, F64 &v)
{
    out >> *((U64 *)&v);
    return out;
}

}
