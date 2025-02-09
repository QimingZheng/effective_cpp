#include <iostream>

void g(std::string s) {}
void g(int x) {}

template <typename T>
void f(T&& x) {
  g(std::forward<T>(x));
}

template <typename T>
T&& myforward(typename std::remove_reference<T>::type& param) {
  return static_cast<T&&>(param);
}

template <typename T>
void f2(T&& x) {
  g(myforward<T>(x));
}

template <typename T>
class A {
 public:
  typedef T&& RvalueRefToT;
  typedef std::remove_reference_t<T>&& RvalueRefToT2;
};

int main() {
  f("");
  f(1);

  f2("");
  f2(1);

  int x = 2;
  f(x);
  f2(x);

  A<int&>::RvalueRefToT a = x;
  A<int&>::RvalueRefToT2 aa = 1;

  return 0;
}