#include <assert.h>

#include <memory>
bool released = false;

class A {
 public:
  A() { x = new int[1000000]; }
  ~A() {
    released = true;
    delete x;
  }

 private:
  int *x;
};

void process(std::shared_ptr<A> ptr, int priority) {}

int cal() { return 1; }

int main() {
  {
    assert(released == false);
    std::weak_ptr<A> wp;
    {
      auto sp = std::make_shared<A>();
      auto sp2 = sp;
      wp = std::weak_ptr<A>(sp2);
    }
    assert(released = true);
  }
  assert(released = true);
  released = false;
  {
    assert(released == false);
    std::weak_ptr<A> wp;
    {
      auto sp = std::shared_ptr<A>(new A);
      wp = std::weak_ptr<A>(sp);
    }
    assert(released = true);
  }
  assert(released = true);

  // Not safe, because if cal() throws, the memory allocated by shared_ptr could
  // be leaked.
  process(std::make_shared<A>(), cal());

  auto p = std::make_shared<A>();

  // safe an efficient.
  process(std::move(p), cal());

  return 0;
}