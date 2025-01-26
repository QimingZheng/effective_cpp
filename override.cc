#include <iostream>

class Base {
 public:
  virtual void f1() const = 0;
  virtual void f2(int x) = 0;
  virtual void f3() & = 0;
  virtual void f4() const = 0;
  virtual void f5() = 0;
};

class Derived : public Base {
 public:
  virtual void f1() const override {}
  virtual void f2(int x) override {}
  virtual void f3() & override {}
  virtual void f4() const override {}
  virtual void f5() final { std::cout << "Derived.f5" << std::endl; }

  using DataType = std::vector<int>;

  DataType& data() & {
    std::cout << "DataType& data() &" << std::endl;
    return val_;
  }
  DataType data() && {
    std::cout << "DataType data() &&" << std::endl;
    return std::move(val_);
  }

 private:
  DataType val_;
};

class DeriveAgain : public Derived {
 public:
  //   virtual void f5() override;
};

int main() {
  Derived d;
  d.f5();

  Derived::DataType x = Derived().data();
  Derived::DataType y = d.data();
  return 0;
}