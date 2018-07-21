#include <cassert>
//
#include <lux/alias/scalar.hpp>
#include <lux/alias/vector.hpp>
#include <lux/serial/serializer.hpp>
#include <lux/serial/deserializer.hpp>

namespace serial
{

template<typename T>
inline Serializer &operator<<(Serializer &in, Vector<T> const &v)
{
    in << v.size();
    for(auto const &i : v) in << i;
    return in;
}

template<typename T>
inline Deserializer &operator>>(Deserializer &out, Vector<T> &v)
{
    SizeT len;
    out >> len;
    for(SizeT i = 0; i < len; ++i)
    {
        out >> v[i];
    }
    return out;
}

}
