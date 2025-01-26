#include <iostream>

int main() {
  std::vector<int> vec{1, 2, 3, 5, 6};

  auto it = std::find(vec.cbegin(), vec.cend(), 3);

  vec.insert(it, 4);

  return 0;
}