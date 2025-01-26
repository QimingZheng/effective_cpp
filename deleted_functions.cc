
bool isLucky(int x) { return x % 2 == 0; }
bool isLucky(char) = delete;
bool isLucky(bool) = delete;
bool isLucky(double) = delete;

template <typename T>
void processPtr(T* ptr) {}

template <>
void processPtr(char*) = delete;

template <>
void processPtr(void*) = delete;

template <typename T>
class A {
 public:
  void processPtr(T* ptr) {}
};

template <>
void A<void>::processPtr(void* ptr) = delete;

int main() {
  isLucky(1);
  // isLucky(1.1);
  // isLucky('a');
  A<void> a;
  //   a.processPtr(nullptr);
  A<int> b;
  b.processPtr(nullptr);
  return 0;
}