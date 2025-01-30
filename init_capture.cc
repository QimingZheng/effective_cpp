#include <assert.h>

#include <memory>

int main() {
  auto pw = std::make_unique<int>(2);
  auto fun = [pw_ = std::move(pw)] {
    assert(*pw_ == 2);
    *pw_ += 1;
    assert(*pw_ == 3);
  };
  fun();
  assert(pw == nullptr);
  return 0;
}
