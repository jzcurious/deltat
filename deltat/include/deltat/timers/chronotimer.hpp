#ifndef _CRONOTIMER_HPP_
#define _CRONOTIMER_HPP_

#include <chrono>

class ChronoTimer final {
  using clock_t = std::chrono::high_resolution_clock;
  using time_point_t = std::chrono::time_point<clock_t>;

 private:
  double& _time;
  time_point_t _start;

 public:
  struct timer_f {};

  ChronoTimer();
  ChronoTimer(double& time);
  ~ChronoTimer();
};

#endif  // _CRONOTIMER_HPP_
