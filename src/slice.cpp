#include <lux_shared/slice.hpp>

template<>
void Slice<U8>::set(U8* beg, SizeT len) {
    this->beg = beg;
    this->len = len;
}
