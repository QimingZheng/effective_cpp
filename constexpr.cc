#include <iostream>
#include <vector>

constexpr size_t pow(int base, int exp) noexcept {
  auto ret = 1;
  while (exp--) {
    ret *= base;
  }
  return ret;
}

class Point {
 public:
  constexpr Point() noexcept : x_(0), y_(0) {}
  constexpr Point(double x, double y) noexcept : x_(x), y_(y) {}
  constexpr double x() const noexcept { return x_; }
  constexpr double y() const noexcept { return y_; }
  constexpr void setX(double x) noexcept { x_ = x; }
  constexpr void setY(double y) noexcept { y_ = y; }

 private:
  double x_, y_;
};

constexpr Point midpoint(const Point& a, const Point& b) noexcept {
  return {
      (a.x() + b.x()) / 2,
      (a.y() + b.y()) / 2,
  };
}

constexpr Point reflect(const Point& a) noexcept {
  Point point;
  point.setX(-a.x());
  point.setY(-a.y());
  return point;
}

int main() {
  constexpr auto x = 5;
  std::array<int, pow(3, x)> results;
  auto z = rand() % 10;
  std::cout << pow(2, z) << std::endl;

  constexpr auto p = Point(1, 2);
  constexpr auto q = Point(2, 1);

  constexpr auto mid = midpoint(p, q);

  constexpr auto r = reflect(mid);

  return 0;
}