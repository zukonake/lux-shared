#include <cassert>
//
#include <lux/alias/scalar.hpp>
#include <lux/alias/array.hpp>
#include <lux/serial/serializer.hpp>
#include <lux/serial/deserializer.hpp>

namespace serial
{

template<typename T, SizeT len>
inline Serializer &operator<<(Serializer &in, Array<T, len> const &v)
{
    for(SizeT i = 0; i < len; ++i) in << v[i];
    return in;
}

template<typename T, SizeT len>
inline Deserializer &operator>>(Deserializer &out, Array<T, len> &v)
{
    for(SizeT i = 0; i < len; ++i) out >> v[i];
    return out;
}

}
