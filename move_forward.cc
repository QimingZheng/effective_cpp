#include <iostream>
class A {
 public:
  A() {}
  A(A&&) { std::cout << "move constructor" << std::endl; }
  A(A&) { std::cout << "copy constructor" << std::endl; }
};

template <typename T>
decltype(auto) mymove(T&& param) {
  using ReturnType = std::remove_reference_t<T>&&;
  return static_cast<ReturnType>(param);
}

class B {
 public:
  B() {}
  B(const B&) { std::cout << "B copy constructor" << std::endl; }
  B(B&&) { std::cout << "B move constructor" << std::endl; }
};

int main() {
  mymove(A());
  A a;
  mymove(a);

  const B b;
  // it actually calls the copy constructor.
  B bb(std::move(b));

  return 0;
}