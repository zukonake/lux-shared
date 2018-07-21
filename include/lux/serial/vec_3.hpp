#include <lux/linear/vec_3.hpp>
#include <lux/serial/serializer.hpp>
#include <lux/serial/deserializer.hpp>

namespace serial
{

template<typename T>
inline Serializer &operator<<(Serializer &in, linear::Vec3<T> const &v)
{
    in << v.x;
    in << v.y;
    in << v.z;
    return in;
}

template<typename T>
inline Deserializer &operator>>(Deserializer &out, linear::Vec3<T> &v)
{
    out >> v.x;
    out >> v.y;
    out >> v.z;
    return out;
}

}
