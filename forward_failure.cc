#include <string>
#include <vector>

void f() {}
void f(int x) {}

void f(std::string s) {}

// void f(std::vector<int> &v) {}

void f(std::initializer_list<int> &) {}

void f(int pf(int)) {}

int process(int) { return 0; }
int process(int, int) { return 0; }

template <typename... Ts>
void fwd(Ts &&...args) {
  f(std::forward<Ts>(args)...);
}

class A {
 public:
  static const int xx = 1;
};

struct B {
  std::uint32_t field_1 : 1, field_2 : 2;
};

int main() {
  fwd(1);
  fwd("123");

  f({1, 2, 3});
  // wrong:  fwd({1, 2, 3});

  auto v = {1, 2, 3};
  fwd(v);

  f(A::xx);
  // wrong: link time error  fwd(A::xx);

  f(process);
  // wrong:  fwd(process);
  using func = int (*)(int);
  func pf = process;
  fwd(pf);

  B b;

  // wrong:  fwd(b.field_1);
  auto field_1 = b.field_1;

  fwd(field_1);

  return 0;
}