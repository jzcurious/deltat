#include "deltat/timers/chronotimer.hpp"

using namespace dt;

static double time_placeholder = 0;

ChronoTimer::ChronoTimer()
    : _time(time_placeholder) {}

ChronoTimer::ChronoTimer(double& time)
    : _time(time)
    , _start(clock_t::now()) {}

ChronoTimer::~ChronoTimer() {
  time_point_t stop = clock_t::now();
  _time += std::chrono::duration<double>(stop - _start).count();
}
