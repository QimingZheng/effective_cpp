#include <iostream>
#include <vector>

template <typename C, typename I>
auto get(C& container, I index)
/* Optional for >=c++14, Required for c++11 `-> decltype(container[index])` */ {
  return container[index];
}

template <typename C, typename I>
decltype(auto) get_reference(C& container, I index) {
  return container[index];
}

template <typename C, typename I>
decltype(auto) get3(C&& /* universal reference */ container, I index) {
  return std::forward<C>(container)[index];
}

class A {
 public:
  A() { std::cout << "A constructor\n"; }
  A(A& a) { std::cout << "A copy constructor\n"; }
  A(A&& a) { std::cout << "A move constructor\n"; }

  ~A() { std::cout << "desctructor\n"; }
};

template <typename T>
decltype(auto) my_move(T&& t) {
  return std::forward<T>(t);
}

int main() {
  std::vector<int> x = {1, 2, 3, 4};
  std::cout << get(x, 1) << std::endl;
  get_reference(x, 1) = 10;
  std::cout << get_reference(x, 1) << std::endl;
  std::cout << get3(std::vector<int>{1, 2, 3, 4, 5}, 1) << std::endl;
  A a = my_move(A());
  return 0;
}