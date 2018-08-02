#include <cassert>
//
#include <lux/alias/scalar.hpp>
#include <lux/alias/vector.hpp>
#include <lux/serial/serializer.hpp>
#include <lux/serial/deserializer.hpp>
#include <lux/serial/get_size.hpp>

namespace serial
{

template<typename T>
inline SizeT get_size(Vector<T> const &v)
{
    SizeT size = sizeof(SizeT); //first, the size of the vector gets sent
    if constexpr(std::is_trivial<T>::value)
    {
        return size + sizeof(T) * v.size();
    }
    else
    {
        for(auto const &i : v)
        {
            size += get_size(i);
        }
        return size;
    }
}

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
    v.resize(len);
    for(SizeT i = 0; i < len; ++i)
    {
        out >> v[i];
    }
    return out;
}

}
