#include <string>
#include <tuple>

class A {
 public:
  enum class Color;
  // wrong:   enum Color2;
  enum Color3 : int;

  enum class Color {
    blue,
    red,
    green,
  };

  enum Color2 {
    blue,
    red,
    green,
  };

  enum Color3 : int {
    blue3 = 1,
    red3 = 2,
    green3 = 3,
  };
};

using UserInfo = std::tuple<std::string, std::string, int>;

enum UserInfoField { name, email, age };

enum class UserInfoField2 { name, email, age };

template <typename E>
constexpr typename std::underlying_type<E>::type cast(E field) {
  return static_cast<std::underlying_type<E>::type>(field);
}

int main() {
  A::Color color = A::Color::blue;
  // wrong:  A::Color color2 = A::blue;
  A::Color2 color2 = A::blue;
  int x = color2 + 3;
  // wrong:   int y = color + 3;

  UserInfo user = {"Alice", "alice@gmail.com", 10};
  std::string user_name = std::get<name>(user);

  std::string user_name2 = std::get<cast(UserInfoField2::name)>(user);

  return 0;
}