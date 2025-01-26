#include <iostream>

class NoexceptMoveContainer {
 public:
  NoexceptMoveContainer(int x = 0) : ptr_(new int(x)) {}
  NoexceptMoveContainer(const NoexceptMoveContainer& other) {
    ptr_ = other.ptr_;
    std::cout << "NoexceptMoveContainer copy constructor " << *ptr_
              << std::endl;
  }
  NoexceptMoveContainer(NoexceptMoveContainer&& other) noexcept {
    std::cout << "NoexceptMoveContainer move constructor " << *other.ptr_
              << std::endl;
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
  }

 private:
  int* ptr_;
};

class ExceptContainer {
 public:
  ExceptContainer(int x = 0) : ptr_(new int(x)) {}

  ExceptContainer(const ExceptContainer& other) {
    ptr_ = other.ptr_;
    std::cout << "ExceptContainer copy constructor " << *ptr_ << std::endl;
  }

  ExceptContainer(ExceptContainer&& other) {
    std::cout << "ExceptContainer move constructor " << *other.ptr_
              << std::endl;
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
  }

 private:
  int* ptr_;
};

int main() {
  std::vector<NoexceptMoveContainer> a;
  std::vector<ExceptContainer> b;

  NoexceptMoveContainer x1(1), x2(2), x3(3);
  a.push_back(x1);
  a.push_back(x2);
  a.push_back(x3);

  ExceptContainer y1(1), y2(2);
  b.push_back(y1);
  b.push_back(y2);

  return 0;
}