#include <map>

template <typename T>
using MyMap = std::map<T, T>;

template <typename T>
class A {
 public:
  MyMap<T> list;
  std::add_const_t<MyMap<T>> const_list;
};

template <typename T>
struct MyMap2 {
  typedef std::map<T, T> type;
};

template <typename T>
class A2 {
 public:
  /* tell the compiler MyMap2<T>::type is a type*/ typename MyMap2<T>::type
      list;

  typename std::add_const<typename MyMap2<T>::type>::type const_list;
};

int main() {
  MyMap<std::string> my_map;

  A<int> a;
  A2<int> a2;
  return 0;
}
