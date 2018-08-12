#pragma once

#include <chrono>

namespace util
{

class Clock
{
    public:
    typedef std::chrono::duration<double> Duration;

    Clock();
    Clock(Clock const &that) = delete;
    Clock &operator=(Clock const &that) = delete;

    void start();
    Duration stop();
    private:
    std::chrono::steady_clock clock;
    std::chrono::time_point<std::chrono::steady_clock> before;
};

}
