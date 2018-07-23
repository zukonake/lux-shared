#include <cassert>
//
#include <lux/alias/scalar.hpp>
#include <lux/alias/array.hpp>
#include <lux/serial/serializer.hpp>
#include <lux/serial/deserializer.hpp>
#include <lux/serial/get_size.hpp>

namespace serial
{

//TODO this is O(n), along with Vector,
// change this to multiply the size of the first element by len,
// as long as the elements do not contain pointers, i.e. the value of
// the element is equal to it's byte-copy, even on another PC
template<typename T, SizeT len>
inline SizeT get_size(Array<T, len> const &v)
{
    SizeT size = 0;
    for(auto const &i : v)
    {
        size += get_size(i);
    }
    return size;
}

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
