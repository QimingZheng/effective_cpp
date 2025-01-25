#include <iostream>
#include <vector>

int main() {
  bool bit1 = std::vector<bool>{false, true, true, true}[2];
  auto bit2 = std::vector<bool>{false, true, true, true}[2];
  auto bit3 = static_cast<bool>(std::vector<bool>{false, true, true, true}[2]);

  std::cout << bit1 << " " << bit2 << " " << bit3 << std::endl;

  return 0;
}