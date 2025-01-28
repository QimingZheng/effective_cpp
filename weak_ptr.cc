#include <assert.h>

#include <iostream>
#include <memory>
#include <unordered_map>

class Factory {
 public:
  auto get(int id) {
    auto ptr = cache_[id].lock();
    if (ptr == nullptr) {
      ptr = std::shared_ptr<int>(new int(id));
      cache_[id] = ptr;
    }
    return ptr;
  }

  size_t valid_cache_size() {
    int count = 0;
    for (auto &entry : cache_) {
      if (entry.second.expired()) continue;
      count++;
    }
    return count;
  }

 private:
  std::unordered_map<int, std::weak_ptr<int>> cache_;
};

class Object {
 public:
  Object(int x) : x_(x) {}
  ~Object() { std::cout << x_ << " is desctructed" << std::endl; }
  void setSharedPtr(std::shared_ptr<Object> other) { other_ = other; }
  void setWeakPtr(std::shared_ptr<Object> other) { other_2_ = other; }

 private:
  std::shared_ptr<Object> other_{nullptr};
  std::weak_ptr<Object> other_2_;
  int x_;
};

int main() {
  std::shared_ptr<int> ptr(new int(42));
  std::weak_ptr<int> wptr(ptr);

  auto sptr = wptr.lock();

  ptr = nullptr;
  sptr = nullptr;

  assert(wptr.expired());

  Factory f;
  assert(f.valid_cache_size() == 0);
  assert(*f.get(1) == 1);
  assert(f.valid_cache_size() == 0);
  assert(*f.get(10) == 10);
  assert(f.valid_cache_size() == 0);
  {
    auto ptr = f.get(100);
    assert(f.valid_cache_size() == 1);
  }
  assert(f.valid_cache_size() == 0);

  {
    std::shared_ptr<Object> a = std::make_shared<Object>(1);
    std::shared_ptr<Object> b = std::make_shared<Object>(2);
    std::shared_ptr<Object> c = std::make_shared<Object>(3);

    a->setSharedPtr(b);
    c->setSharedPtr(b);
    b->setWeakPtr(a);
  }
  {
    std::shared_ptr<Object> a = std::make_shared<Object>(1);
    std::shared_ptr<Object> b = std::make_shared<Object>(2);
    std::shared_ptr<Object> c = std::make_shared<Object>(3);

    a->setSharedPtr(b);
    c->setSharedPtr(b);
    b->setSharedPtr(a);
  }

  return 0;
}