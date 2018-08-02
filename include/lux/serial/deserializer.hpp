#pragma once

#include <cassert>
//
#include <lux/alias/scalar.hpp>
#include <lux/alias/vector.hpp>
#include <lux/alias/array.hpp>
#include <lux/net/net_order.hpp>
#include <lux/serial/clear_buffer.hpp>

namespace serial
{

class Deserializer
{
    public:
    void set_slice(U8 const *start, U8 const *end);

    friend Deserializer &operator>>(Deserializer &out, U8  &v);
    friend Deserializer &operator>>(Deserializer &out, U16 &v);
    friend Deserializer &operator>>(Deserializer &out, U32 &v);
    friend Deserializer &operator>>(Deserializer &out, U64 &v);

    SizeT get_size() const;

    private:
    U8 const *iter;
    U8 const *end;
};

template<typename T>
inline void deserialize(Deserializer &out, T &buf, U8 const *start, U8 const *_end)
{
    serial::clear_buffer(buf);
    out.set_slice(start, _end);
    out >> buf;
}

inline void Deserializer::set_slice(U8 const *_start, U8 const *_end)
{
    iter = _start;
    end  = _end;
}

inline SizeT Deserializer::get_size() const
{
    return (SizeT)(end - iter);
}

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
    net::net_memcpy((U8 *)&v, out.iter, 2);
    out.iter += 2;
    return out;
}

inline Deserializer &operator>>(Deserializer &out, U32 &v)
{
    assert(out.get_size() >= 4);
    net::net_memcpy((U8 *)&v, out.iter, 4);
    out.iter += 4;
    return out;
}

inline Deserializer &operator>>(Deserializer &out, U64 &v)
{
    assert(out.get_size() >= 8);
    net::net_memcpy((U8 *)&v, out.iter, 8);
    out.iter += 8;
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

inline Deserializer &operator>>(Deserializer &out, char &v)
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
