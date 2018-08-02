#pragma once

#include <thread>
#include <chrono>

namespace util
{

class TickClock
{
    public:
    typedef std::chrono::steady_clock Clock;
    typedef std::chrono::duration<double> Duration;
    typedef std::chrono::time_point<Clock> TimePoint;

    TickClock(Duration rate);
    TickClock(TickClock const &that) = delete;
    TickClock &operator=(TickClock const &that) = delete;

    void reset();
    void start();
    void stop();
    void set_rate(Duration value);
    Duration get_tick_len();
    Duration synchronize();
    private:
    Clock clock;
    Duration  cycle;
    Duration  rate;
    TimePoint before;
};

}
