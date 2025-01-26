#include <atomic>
#include <mutex>

class A {
 public:
  void test() const noexcept { ++count; }

  mutable std::atomic<int> count{0};
};

class B {
 public:
  int test() const noexcept {
    if (cached) return cached_result;
    std::lock_guard<std::mutex> guard(mtx);
    cached_result = rand();
    cached = true;
    return cached_result;
  }

  mutable std::mutex mtx;
  mutable bool cached{false};
  mutable int cached_result;
};

int main() { return 0; }