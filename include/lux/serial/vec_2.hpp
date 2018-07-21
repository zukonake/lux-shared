#include <lux/linear/vec_2.hpp>
#include <lux/serial/serializer.hpp>
#include <lux/serial/deserializer.hpp>

namespace serial
{

template<typename T>
inline Serializer &operator<<(Serializer &in, linear::Vec2<T> const &v)
{
    in << v.x;
    in << v.y;
    return in;
}

template<typename T>
inline Deserializer &operator>>(Deserializer &out, linear::Vec2<T> &v)
{
    out >> v.x;
    out >> v.y;
    return out;
}

}
