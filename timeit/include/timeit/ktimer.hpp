#ifndef _KTIMER_HPP_
#define _KTIMER_HPP_

#include <concepts>

template <class T>
concept TimerKind
    = std::constructible_from<T, double&> and not std::constructible_from<T, double>;

#endif  // _KTIMER_HPP_
