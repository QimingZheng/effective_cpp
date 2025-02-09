#include <vector>

class W {
 public:
};

// universal reference
template <typename T>
void f1(T&& v) {}

// rvalue reference
template <typename T>
void f2(std::vector<T>&&) {}

// rvalue reference
template <typename T>
void f3(const T&& v) {}

template <class T>
class Vec {
 public:
  // rvalue reference
  void push_back(T&&) {}

  // universal reference
  template <class... Args>
  void emplace_back(Args&&... args) {}
};

int main() {
  // rvalue reference.
  auto&& a = W();
  W w;
  // reference
  auto&& b = w;

  // wrong:  f3(w);
  f3(W());

  Vec<int> v;
  int aa = 1;
  v.emplace_back(1);
  v.emplace_back(aa);

  // wrong:   v.push_back(aa);
  v.push_back(std::move(aa));

  return 0;
}