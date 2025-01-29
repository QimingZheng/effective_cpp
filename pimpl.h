#include <memory>
#include <string>

class A {
 public:
  A();

  A(const A& a);
  A& operator=(const A& a);
  A(A&& a);
  A& operator=(A&& a);

 private:
  struct Impl;
  std::unique_ptr<Impl> pImpl;
};
