#include <atomic>
#include <iostream>
#include <vector>

class A {
 private:
  int x{0};
  int y = 0;
  //   int z(0);
};

class B {};

class C {
 public:
  C() { std::cout << "default constructor" << std::endl; }
  C(int x, bool y) { std::cout << "constructor(int, bool)" << std::endl; }
  C(std::initializer_list<double> init) {
    std::cout << "constructor(initializer_list<double>)" << std::endl;
  }

  C(C& c) { std::cout << "copy constructor" << std::endl; }

  operator float() const { return 1.0f; }
};

template <typename T, typename... Ts>
void doSomeWork(Ts&&... params) {
  T localObject1(std::forward<Ts>(params)...);
  T localObject2{std::forward<Ts>(params)...};
}

int main() {
  auto x(0);
  auto y = 0;
  int z{0};

  std::atomic<int> ai1{0};
  std::atomic<int> ai2(0);
  // wrong when <c++20:   std::atomic<int> ai3 = 0;

  double x1 = .1, y1 = .2, z1 = .4;
  //   int sum1{x1 + y1 + z1};
  int sum2(x1 + y1 + z1);
  int sum3 = x1 + y1 + z1;

  // This is defining a function named b, with return type B.
  B b();

  std::cout << typeid(b).name() << std::endl;

  B bb{};
  std::cout << typeid(bb).name() << std::endl;

  C c{1, true};
  C cc(1, true);

  C ccc(c);
  C cccc{c};

  C c5({});
  C c6;
  C c7{};
  C c8{{}};

  doSomeWork<std::vector<int>>(1, 2);

  return 0;
}