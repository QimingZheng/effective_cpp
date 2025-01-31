#include <assert.h>

#include <chrono>
#include <future>
using namespace std::chrono_literals;

template <typename F, typename... Ts>
inline auto realAsync(F&& f, Ts&&... params) {
  return std::async(std::launch::async, std::forward<F>(f),
                    std::forward<Ts>(params)...);
}

int main() {
  auto flag = false;
  auto f = [&]() { flag = true; };

  auto fut1 = std::async(f);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  assert(flag == true);
  fut1.get();

  flag = false;
  auto fut2 = std::async(std::launch::deferred, f);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  assert(fut2.wait_for(std::chrono::microseconds(0)) ==
         std::future_status::deferred);
  assert(flag == false);
  fut2.get();
  assert(flag == true);

  flag = false;
  auto fut3 = realAsync(f);
  fut3.get();
  assert(flag == true);

  return 0;
}