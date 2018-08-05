#pragma once

#define REGISTER_NET_FUNCTIONS(ident) \
    class Serializer; \
    class Deserializer; \
    SizeT get_size( ident const &v); \
    void clear_buffer( ident &v); \
    Serializer &operator<<(Serializer &in, ident const &v); \
    Deserializer &operator>>(Deserializer &out, ident &v);
