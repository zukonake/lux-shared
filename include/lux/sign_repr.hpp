#pragma once

#define SIGN_REPR_UNKNOWN            0
#define SIGN_REPR_SIGN_AND_MAGNITUDE 1
#define SIGN_REPR_ONES_COMPLEMENT    2
#define SIGN_REPR_TWOS_COMPLEMENT    3

#define SIGN_REPR (-1 & 3)

#if SIGN_REPR == SIGN_REPR_UNKNOWN
#   warning "unknown signed representation, expect glitches"
#endif
