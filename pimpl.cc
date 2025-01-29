#include "pimpl.h"

#include <memory>
#include <string>

struct A::Impl {
  std::string name;
};

A::A() : pImpl(std::make_unique<Impl>()) {}

A::A(const A& a) : pImpl(std::make_unique<Impl>(*a.pImpl)) {}
A::A(A&& a) = default;
A& A::operator=(A&& a) = default;

A& A::operator=(const A& a) {
  *pImpl = *a.pImpl;
  return *this;
}

int main() {
  A a;
  A b = std::move(a);
  return 0;
}