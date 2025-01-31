#include <future>
#include <thread>

class ThreadRAII {
 public:
  enum class DtorAction { join, detach };
  ThreadRAII(std::thread&& t, DtorAction action)
      : t_(std::move(t)), action_(action) {}

  ~ThreadRAII() {
    if (t_.joinable()) {
      if (action_ == DtorAction::join) {
        t_.join();
      } else {
        t_.detach();
      }
    }
  }

  ThreadRAII(ThreadRAII&&) = default;
  ThreadRAII& operator=(ThreadRAII&&) = default;

  std::thread& get() { return t_; }

 private:
  DtorAction action_;
  std::thread t_;
};

int main() {
  auto f = [](std::function<bool(int)> filter, int range) {
    std::vector<int> vals;
    ThreadRAII t(std::thread([&filter, range, &vals] {
                   for (auto i = 1; i <= range; i++)
                     if (filter(i)) vals.push_back(i);
                 }),
                 ThreadRAII::DtorAction::join);
    if (false) {
      t.get().join();
      return true;
    }
    return false;
  };

  auto fut = std::async(f, [](int x) { return x % 1025 == 1; }, 10'000'000);
  fut.get();

  return 0;
}
