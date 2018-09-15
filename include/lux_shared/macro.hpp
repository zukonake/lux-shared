#pragma once

#include <cstdio>
#include <cstdlib>

#ifdef defer
    #error "defer macro is already defined"
#endif

///zero-overhead defer mechanism in c++, neat
struct DeferDummy {};
template<typename F>
struct Deferrer
{
    F f;
    ~Deferrer() { f(); }
};
template<typename F>
Deferrer<F> operator*(DeferDummy, F f) { return {f}; }
#define DEFER_(LINE) zz_defer##LINE
#define DEFER(LINE) DEFER_(LINE)
#define defer auto DEFER(__LINE__) = DeferDummy { } *[&]()

//@TODO use tinyprintf
#define LUX_LOG(fmt, ...) { \
    std::printf("%s(): " fmt "\n", __func__ __VA_OPT__(,) __VA_ARGS__); }

#define LUX_FATAL(fmt, ...) { \
    std::fprintf(stderr, "FATAL %s(): " fmt "\n", \
            __func__ __VA_OPT__(,) __VA_ARGS__); \
    std::quick_exit(EXIT_FAILURE); }

#define LUX_PANIC(fmt, ...) { \
    std::fprintf(stderr, "PANIC %s(): " fmt "\n", \
            __func__ __VA_OPT__(,) __VA_ARGS__); \
    std::abort(); }

//we don't want our code to call assert from <assert.h>
#undef assert

#ifndef NDEBUG
    #define LUX_ASSERT(expr) { \
        if(!(expr)) LUX_PANIC("assertion `" #expr "` failed"); }
#else
    #define LUX_ASSERT(expr) do {} while(false)
#endif

#define LUX_SIGN_REPR_UNKNOWN            0
#define LUX_SIGN_REPR_SIGN_AND_MAGNITUDE 1
#define LUX_SIGN_REPR_ONES_COMPLEMENT    2
#define LUX_SIGN_REPR_TWOS_COMPLEMENT    3

#define LUX_SIGN_REPR (-1 & 3)

#if LUX_SIGN_REPR != LUX_SIGN_REPR_SIGN_AND_MAGNITUDE &&  \
    LUX_SIGN_REPR != LUX_SIGN_REPR_ONES_COMPLEMENT    &&  \
    LUX_SIGN_REPR != LUX_SIGN_REPR_TWOS_COMPLEMENT
#   warning "unknown signed representation"
#endif
