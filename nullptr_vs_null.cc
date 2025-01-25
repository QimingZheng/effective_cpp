#include <iostream>
#include <mutex>
void f(int) { std::cout << "f(int)" << std::endl; }
void f(int*) { std::cout << "f(int*)" << std::endl; }

void f1(std::shared_ptr<int> sp) {}
void f2(std::unique_ptr<int> uq) {}
void f3(int* p) {}

using MtxGuard = std::lock_guard<std::mutex>;

template <typename FuncType, typename MtxType, typename PtrType>
auto lockAndCall(FuncType func, MtxType& mtx, PtrType ptr) {
  MtxGuard mtx_guard(mtx);
  return func(ptr);
}

int main() {
  // this is ambiguous:   f(NULL);
  f(nullptr);

  std::mutex mtx;
  //   lockAndCall(f1, mtx, 0);
  //   lockAndCall(f2, mtx, NULL);
  lockAndCall(f3, mtx, nullptr);
  return 0;
}