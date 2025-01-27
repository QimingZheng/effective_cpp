#include <assert.h>

#include <memory>
#include <vector>

int counter = 0;

auto delFunc = [](int *x) {
  counter++;
  delete x;
};

void func() { std::shared_ptr<int> x(new int(1), delFunc); }

class A : public std::enable_shared_from_this<A> {
 public:
  A() {}
  void process() {
    // wrong: a_.emplace_back(this);
    a_.emplace_back(shared_from_this());
  }

 private:
  std::vector<std::shared_ptr<A>> a_;
};

int main() {
  std::shared_ptr<int> ptr(new int(3));

  std::shared_ptr<int> ptr2 = std::move(ptr);
  assert(ptr == nullptr);
  assert(*ptr2 == 3);

  assert(counter == 0);
  func();
  assert(counter == 1);

  // A a;
  // throw:  a.process();

  auto a = std::make_shared<A>(A());
  a->process();

  return 0;
}