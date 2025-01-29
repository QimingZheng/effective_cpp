#include <assert.h>

#include <iostream>
#include <vector>

using FilterContainer = std::vector<std::function<bool(int)>>;

class A {
 public:
  void addFilter(FilterContainer& filters) {
    // won't compile, divisor is not capturable:
    // filters.emplace_back([divisor](int val) { return val % divisor == 0; });

    // `=` is actually capturing `this` pointer.
    filters.emplace_back([=](int val) { return val % divisor == 0; });
  }

  void addFilter2(FilterContainer& filters) {
    filters.emplace_back(
        // generalized lambda capture
        [divisor_ = divisor](int val) { return val % divisor_ == 0; });
  }

  void addFilter3(FilterContainer& filters) {
    static auto div = 5;
    filters.emplace_back(
        // div is not captured at all!
        [=](int val) { return val % div == 0; });
    div = 3;
  }

  int divisor = 5;
};

int main() {
  FilterContainer filters;
  {
    auto divisor = 5;
    filters.emplace_back(
        [&divisor](const auto& value) { return value % divisor == 0; });
    assert((*filters.begin())(10) == true);
    divisor = 3;
  }

  // actually the behavior is undefined
  assert((*filters.begin())(10) == false);

  A a;

  filters.pop_back();
  a.addFilter(filters);

  assert((*filters.begin())(10) == true);
  a.divisor = 3;
  assert((*filters.begin())(10) == false);

  a.divisor = 5;
  filters.pop_back();
  a.addFilter2(filters);
  assert((*filters.begin())(10) == true);
  a.divisor = 3;
  assert((*filters.begin())(10) == true);

  filters.pop_back();
  a.addFilter3(filters);
  assert((*filters.begin())(10) == false);

  return 0;
}