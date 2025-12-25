#include "../include/instruments/americanOption.h"
#include "../include/models/binomial.h"
#include <memory>

#include <memory>
#include <iostream>

int main() {
  double K = 50; // Strike price
  double T = 0.41666666666; // Maturity
  double S0 = 52;
  double r = 0.1;
  double sigma = 0.4;
  double divVal = 2.06;
  double divTime = 0.29166666666;
  char optType = 'p';

  auto amerOpt = std::make_shared<AmericanOption>(optType,K,T);
  Dividend::CashFlow cash1{divTime,divVal};

  std::vector<Dividend::CashFlow> cashVec = {cash1};
  auto dividends = std::make_shared<DiscreteDividend>(cashVec);
  auto stock = std::make_shared<Stock>(S0,dividends);

  BinomialModel binom(amerOpt, stock, r, sigma, 100);
  double price = binom.getPrice();
  std::cout << price << std::endl;
}
