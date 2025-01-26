#include <memory>

class Investment {
 public:
  virtual ~Investment() {}
};

class Stock : public Investment {
 public:
};

class Bond : public Investment {
 public:
};

class RealEstate : public Investment {
 public:
};

enum class InvestmentType { stock, bond, real_estate };

template <typename... Ts>
auto makeInvestment(InvestmentType type, Ts&&... params) {
  auto delInvmt = [](Investment* investment) {
    // Do Somthing.
    delete investment;
  };
  std::unique_ptr<Investment, decltype(delInvmt)> pInv(nullptr, delInvmt);
  switch (type) {
    case InvestmentType::bond:
      pInv.reset(new Bond(std::forward<Ts>(params)...));
      break;
    case InvestmentType::stock:
      pInv.reset(new Stock(std::forward<Ts>(params)...));
      break;
    case InvestmentType::real_estate:
      pInv.reset(new RealEstate(std::forward<Ts>(params)...));
      break;
  }
  return pInv;
}

int main() {
  auto bond_inv = makeInvestment(InvestmentType::bond);
  auto stock_inv = makeInvestment(InvestmentType::stock);

  auto arr_ptr = std::make_unique<int[]>(5);
  arr_ptr[0] = 1;
  arr_ptr[1] = 2;
  auto x = arr_ptr[1];

  std::shared_ptr<Investment> shared_ =
      makeInvestment(InvestmentType::real_estate);
  return 0;
}