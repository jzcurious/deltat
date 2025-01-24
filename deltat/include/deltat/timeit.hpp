#ifndef _TIMEIT_CUH_
#define _TIMEIT_CUH_

#include "timers/ktimer.hpp"

#include <sys/types.h>
#include <vector>

namespace dt::detail {

template <class T>
concept TimeItKind = requires { typename T::TimeItFeature{}; };

template <typename T>
concept TupleLike = requires(T a) {
  std::tuple_size<T>::value;
  std::get<0>(a);
};

template <TupleLike T>
auto make_indices_for_tuple(T) {
  return std::make_index_sequence<std::tuple_size_v<T>>{};
}

template <TimeItKind TimeItT, class TupleT, std::size_t... I>
void apply_timeit(TimeItT& timeit, const TupleT& args_tuple, std::index_sequence<I...>) {
  timeit.run(std::get<I>(args_tuple)...);
}

}  // namespace dt::detail

namespace dt {

template <class TargetT, TimerKind TimerT>
class TimeIt final {
 private:
  const TargetT& _target;
  const uint _nwarmups;
  const uint _nrepeats;
  std::vector<double> _metrics;

 public:
  struct TimeItFeature {};

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

  template <detail::TupleLike ArgTupleT>
  double run(ArgTupleT& args) {
    return detail::apply_timeit(*this, args, detail::make_indices_for_tuple(args));
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
