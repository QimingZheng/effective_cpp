#include <future>
#include <iostream>

int main() {
  auto f = [](auto n) {
    auto count = 0;
    for (auto i = 2; i < n; i++) {
      auto is_prime = true;
      for (auto j = 2; j * j <= i; j++) {
        if (i % j == 0) {
          is_prime = false;
        }
      }
      if (is_prime) {
        std::cout << i << " ";
        count += 1;
      }
    }
    std::cout << std::endl;
    return count;
  };

  auto fut = std::async(f, 100);
  std::cout << fut.get() << std::endl;

  auto exception_f = []() { throw std::runtime_error("some exception"); };

  auto fut2 = std::async(exception_f);

  try {
    fut2.get();
  } catch (std::runtime_error &e) {
    std::cout << "exceptions\n";
  }
  return 0;
}
