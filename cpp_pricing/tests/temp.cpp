#include "../include/instruments/americanOption.h"
#include "../include/models/binomial.h"
#include <memory>

#include <memory>
#include <iostream>

int main() {
  double K = 30; // Strike price
  double T = 2; // Maturity
  double S0 = 100;
  double r = 0.02;
  auto exercise = std::make_shared<AmericanExercise>(1.0); // T = 1 year
  auto payoff   = std::make_shared<CallPayoff>(100.0);     // K = 100

  Option ameCall(exercise, payoff);
  double pay = ameCall.payoff().getPayoff(200);
  std::cout << pay << std::endl;

  auto amerOpt = std::make_shared<AmericanOption>('c',40.0, 2.0);
  std::cout << amerOpt->canExercise(3.0) << std::endl;
  std::cout << amerOpt->canExercise(1.5) << std::endl;
  std::cout << amerOpt->getPayoff(50) << std::endl;

  Dividend::CashFlow cash1{0.2,20};
  Dividend::CashFlow cash2{0.4,20};
  Dividend::CashFlow cash3{0.6,20};

  std::vector<Dividend::CashFlow> cashVec = {cash1, cash2, cash3};
  auto dividends = std::make_shared<DiscreteDividend>(cashVec);
  auto stock = std::make_shared<Stock>(100,dividends);

  BinomialModel binom(amerOpt, stock, 0.2, 0.09);
  double price = binom.getPrice();
  std::cout << price << std::endl;










}
