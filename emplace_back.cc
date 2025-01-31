#include <vector>

int main() {
  std::vector<std::string> x;
  x.push_back("a");
  x.emplace_back("a");
  x.emplace_back(50, "a");
  return 0;
}