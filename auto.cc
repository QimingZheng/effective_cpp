#include <iostream>
#include <unordered_map>
#include <vector>

template <typename It>
void dwim(It b, It e) {
  while (b != e) {
    auto cur = *b;
    std::cout << cur << " ";
    b++;
  }
  std::cout << "\n";
}

int main() {
  auto x = {1, 3, 2};
  dwim(x.begin(), x.end());

  auto func = [](const auto &p1, const auto &p2) { return *p1 < *p2; };

  auto x1 = std::make_shared<int>(1), x2 = std::make_shared<int>(2);
  std::cout << func(x1, x2) << std::endl;

  std::unordered_map<std::string, int> m;

  for (const auto &p : m) {
  }

  return 0;
}