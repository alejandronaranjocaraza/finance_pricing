#include "../include/instruments/americanOption.h"
#include "../include/instruments/europeanOption.h"
#include "../include/models/binomial.h"
#include "../include/models/bsm.h"

#include "../include/exercise/europeanExercise.h"

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
  auto euroOpt = std::make_shared<EuropeanOption>(optType,K,T);
  
  Dividend::CashFlow cash1{divTime,divVal};
  std::vector<Dividend::CashFlow> cashVec = {cash1};
  
  auto dividends = std::make_shared<ContinuousDividend>(0.0);

  auto stockPtr = std::make_shared<Stock>(S0,dividends);
  
  auto exercisePtr = std::make_shared<EuropeanExercise>();
  auto payoffPtr  = std::make_shared<PutPayoff>();

  // VanillaOption::OptionType optType2 = VanillaOption::OptionType::put;
  auto vanillaOptPtr = std::make_shared<VanillaOption>(
      K,
      T,
      exercisePtr,
      payoffPtr
      );

  BinomialModel binom(vanillaOptPtr, stockPtr, r, sigma, 500);
  double price = binom.getPrice();
  std::cout << price << std::endl;
  
  BSM bsm(
      vanillaOptPtr,
      stockPtr,
      r,
      sigma
      );

  double bsmPrice = bsm.getPrice();
  std::cout << bsmPrice << std::endl;
  
  double bsmVega = bsm.greeks().vega(0.3);
  std::cout << bsmVega << std::endl;

  double impliedVol = bsm.impliedVol(8.3);
  std::cout << impliedVol << std::endl;
}
