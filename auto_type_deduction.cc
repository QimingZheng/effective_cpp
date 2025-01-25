// g++ --std=c++11 auto_type_deduction.cc
#include <iostream>

void someFunc(double, int) {}

template <typename T>
void f(std::initializer_list<T> initList) {}

int main() {
  auto x = 10;  // case 3

  const auto cx = x;  // case 3

  const auto& rx = x;  // case 1

  auto&& uref1 = x;

  auto&& uref2 = cx;

  auto&& uref3 = 27;

  const char name[] = "hello world";

  auto arr = name;
  auto& arr1 = name;

  std::cout << arr << std::endl;

  std::cout << arr1 << std::endl;

  auto func = someFunc;
  auto& func_ref = someFunc;

  auto x1 = 27;
  auto x2(27);
  auto x3 = {27};
  auto x4{27};

  f({1, 2, 3, 4});

  std::cout << x1 << " " << x2 << " " << x3.size() << " " << x4 << std::endl;

  return 0;
}