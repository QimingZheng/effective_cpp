#include <iostream>

class A {
 public:
  A() {}
  A(A&& other) {}
};

class B {
 public:
  B() {}
  B(B& b) {}
};

class C {
 public:
  C() {}
  ~C() {}

  C(C&) = default;
  C(C&&) = default;
  C& operator=(C&&) = default;
};

int main() {
  A a;
  // Copy constructor is not auto-generated: A aa = a;

  B b;
  // Move constructor is not auto-generated: B bb = std::move(b);

  C c;
  C cc = c;
  C ccc = std::move(c);

  return 0;
}