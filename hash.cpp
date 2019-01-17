#include <lux_shared/hash.hpp>

SizeT merge_hash(SizeT a, SizeT b) {
    //@TODO not sure how good this is
    return a ^ (b + 0x9e3779b97f4a7c15 + (a << 6) + (a >> 2));
}
