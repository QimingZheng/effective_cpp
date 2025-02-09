#include <iostream>

class Matrix {
 public:
  Matrix() = default;
  Matrix(const Matrix&) { std::cout << "copy" << std::endl; }
  Matrix(Matrix&&) { std::cout << "move" << std::endl; }
};

Matrix operator+(Matrix&& lhs, const Matrix&& rhs) {
  // in-place change lhs
  return std::move(lhs);
}

template <typename T>
Matrix doSthThenCopy(T&& m) {
  // do sth.
  return std::forward<T>(m);
}

int main() {
  Matrix a = Matrix() + Matrix();

  // lvalue reference -> copy.
  Matrix b = doSthThenCopy(a);

  // rvalue reference -> move
  Matrix bb = doSthThenCopy(Matrix());

  return 0;
}