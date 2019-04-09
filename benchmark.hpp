#pragma once

#include <chrono>
//
#include <lux_shared/string.hpp>
#include <lux_shared/macro.hpp>

template<typename F>
void benchmark(Str const& str, F64 threshold, F f) {
    using namespace std::chrono;
    time_point<steady_clock> start = steady_clock::now();
    f();
    time_point<steady_clock> end = steady_clock::now();
    duration<double> dur = end - start;
    if(dur.count() > threshold) {
        LUX_LOG_DBG("benchmark \"%.*s\": %Fs exceeded threshold of %Fs",
            (int)str.len, str.beg, dur.count(), threshold);
    }
}
