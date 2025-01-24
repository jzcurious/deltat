#ifndef _TIMEIT_CUH_
#define _TIMEIT_CUH_

#include "timers/ktimer.hpp"

#include <sys/types.h>
#include <vector>

namespace dt {

template <class TargetT, TimerKind TimerT>
class TimeIt final {
 private:
  const TargetT& _target;
  const uint _nwarmups;
  const uint _nrepeats;
  std::vector<double> _metrics;

 public:
  TimeIt(const TargetT& target, TimerT, uint nrepeats = 1, uint nwarmups = 0)
      : _target(target)
      , _nwarmups(nwarmups)
      , _nrepeats(nrepeats) {}

  template <class... ArgTs>
    requires(std::invocable<TargetT, ArgTs...>)
  double run(ArgTs&&... args) {
    for (uint i = 0; i < _nwarmups; ++i) _target(std::forward<ArgTs>(args)...);

    double total = 0;
    for (uint i = 0; i < _nrepeats; ++i) {
      TimerT t(total);  // NOLINT
      _target(std::forward<ArgTs>(args)...);
    }

    _metrics.push_back(total / _nrepeats);
    return last();
  }

  double last() const {
    if (_metrics.empty()) return -1.0f;
    return _metrics.back();
  }

  const std::vector<double>& metrics() const {
    return _metrics;
  }

  void reset() {
    _metrics.clear();
  }
};

}  // namespace dt

#endif  // _TIMEIT_CUH_
