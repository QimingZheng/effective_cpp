// g++ --std=c++20 template_type_deduction.cc

#include <iostream>
#include <vector>

// Case 1: ParamType is a reference or pointer, but not universal reference
template <typename T>
void f(T &param) {
  std::cout << &param << std::endl;
}

template <typename T>
void f2(const T &param) {
  std::cout << &param << std::endl;
}

template <typename T>
void f3(T *param) {
  std::cout << param << std::endl;
}

// Case 2: ParamType is universal reference.
template <typename T>
void f4(T &&param) {
  std::cout << param << std::endl;
}

// Case 3: ParamType is neither pointer nor reference.
template <typename T>
void f5(T param) {
  std::cout << param << std::endl;
}

template <typename T, size_t N>
constexpr size_t GetArrayElementCount(T (&)[N]) noexcept {
  return N;
}

void someFunc(double, int) {}

int main() {
  int x = 0;
  const int cx = x;
  const int &rx = x;
  f(x);
  f(cx);
  f(rx);

  f2(x);
  f2(cx);
  f2(rx);

  const int *px = &x;
  f3(&x);
  f3(px);

  f4(x);
  f4(4 + 1);

  f5(x);
  f5(cx);
  f5(rx);

  const char *const ptr = "hello world";
  f5(ptr);

  const char name[] = "hello";
  const char *name_ptr = name;

  // array-to-pointer decay.
  f5(name);
  f(name);

  // function-to-pointer decay.
  f5(someFunc);
  f(someFunc);

  std::cout << "Length of " << name << " = " << GetArrayElementCount(name)
            << std::endl;

  int vals[] = {1, 2, 3, 4, 5};
  int vals2[GetArrayElementCount(vals)];

  return 0;
}