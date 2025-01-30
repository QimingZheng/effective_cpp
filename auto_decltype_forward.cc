#include <iostream>
#include <memory>

template <typename T, typename... Ts>
void test(T t, Ts... ts) {
  std::cout << t << std::endl;
  if constexpr (sizeof...(ts) > 0) test(ts...);
}

int main() {
  auto f = [](auto&& x) { return std::forward<decltype(x)>(x); };
  auto x = "abcd";
  f(x);
  f(10);

  auto f2 = [](auto&&... params) {
    return test(std::forward<decltype(params)>(params)...);
  };
  f2(10, x);
  return 0;
}