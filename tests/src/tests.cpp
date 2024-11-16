#include "timeit/timeit.hpp"

#include "gtest/gtest.h"
#include <chrono>
#include <ratio>
#include <thread>

using namespace std;

template <class UnitsT>
void sleep_n(size_t n) {
  std::this_thread::sleep_for(std::chrono::duration<double, UnitsT>{n});
}

#define __sleep_test(_n, _units, _rtol, _atol)                                           \
  TEST(SleepTest, _n##_units##sec) {                                                     \
    TimeIt ti(sleep_n<_units>, ChronoTimer{}, 3, 1);                                     \
    EXPECT_NEAR(ti.run(_n) * _units::den, _n, _n * _rtol + _atol);                       \
  }

#define __sleep_tests_1_1000(_units, _rtol, _atol)                                       \
  __sleep_test(1, _units, _rtol, _atol);                                                 \
  __sleep_test(10, _units, _rtol, _atol);                                                \
  __sleep_test(100, _units, _rtol, _atol);                                               \
  __sleep_test(1000, _units, _rtol, _atol);

__sleep_tests_1_1000(milli, 0.1, 0.1);
__sleep_tests_1_1000(micro, 0.1, 100);
__sleep_tests_1_1000(nano, 0.1, 100'000);
