#pragma once

#include <cassert>
#include <cstring>
//
#include <alias/scalar.hpp>
#include <alias/c_array.hpp>
#include <alias/vector.hpp>
#include <net/net_order.hpp>

namespace net
{

class Deserializer
{
    public:
    Deserializer(U8 const *start, U8 const *end) :
        iter(start),
        end(end)
    { }
    ~Deserializer()
    {
        for(auto &i : allocated_data) free(i);
    }

    friend Deserializer &operator>>(Deserializer &out, U8  &v);
    friend Deserializer &operator>>(Deserializer &out, U16 &v);
    friend Deserializer &operator>>(Deserializer &out, U32 &v);
    friend Deserializer &operator>>(Deserializer &out, U64 &v);
    template<typename T, SizeT len>
    friend Deserializer &operator>>(Deserializer &out, T (&v)[len]);
    template<typename T>
    friend Deserializer &operator>>(Deserializer &out, CArray<T> &v);

    SizeT get_size() const { return (SizeT)(end - iter); }

    private:
    U8 const *iter;
    U8 const *end;
    Vector<void *> allocated_data;
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

template<typename T, SizeT len>
inline Deserializer &operator>>(Deserializer &out, T (&v)[len])
{
    assert(out.get_size() >= len * sizeof(T));
    for(SizeT i = 0; i < len; ++i) out >> val[i];
    return out;
}

template<>
inline Deserializer &operator>>(Deserializer &out, CArray<U8> &v)
{
    out >> v.len;
    assert(out.get_size() >= v.len);
    v.val = std::malloc(v.len);
    //TODO ^ check for nullptr
    //       optimize with realloc
    std::memcpy(v.val, out.iter, v.len);
    out.iter += v.len;
    return out;
}

template<typename T>
inline Deserializer &operator>>(Deserializer &out, CArray<T> &v)
{
    out >> v.len
    assert(out.get_size() >= v.len * sizeof(T));
    v.val = std::malloc(v.len * sizeof(T));
    //TODO ^ check for nullptr
    //       optimize with realloc
    for(SizeT i = 0; i < v.len; ++i) out >> v.val[i];
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
