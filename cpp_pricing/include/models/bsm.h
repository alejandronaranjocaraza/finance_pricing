#pragma once

#include "../../include/instruments/option.h"
#include "../../include/instruments/vanillaOption.h"
#include "../../include/instruments/stock.h"
#include "../algorithms/rootFind/newtonRaphson.h"

#include <memory>

class BSM;

// Analytical Greeks
// Still missing:
//  - Finite Dffference (FD) Greeks
//  - Monte Carlo (MC) Greeks
struct Greeks {
  explicit Greeks(const BSM* owner) : bsm{owner} {}
  const BSM* bsm;
  double delta(double sigma) const;
  double theta(double sigma) const;
  double gamma(double sigma) const;
  double vega(double sigma) const;
};

class BSM {
friend struct Greeks;
public:
  BSM(
      std::shared_ptr<const VanillaOption> optionPtr,
      std::shared_ptr<const Stock> stockPtr,
      double r,
      double sigma
      ) :
    optionPtr_{std::move(optionPtr)},
    stockPtr_{std::move(stockPtr)},
    r_{r},
    sigma_{sigma},
    T_{optionPtr_->maturity()},
    K_{optionPtr_->strikePrice()},
    S0_{stockPtr_->spot()},
    optionType_{optionPtr_->type()}
  {}

  double getD1(double sigma) const;

  double getD2(double sigma) const;

  double getPrice() const;
  
  double getPrice(double sigma);

  double getPutPrice(double sigma) const;

  double getCallPrice(double sigma) const;

  Greeks greeks();

  double impliedVol(double targetPrice);

private:
    std::shared_ptr<const VanillaOption> optionPtr_;
    std::shared_ptr<const Stock> stockPtr_;
    double r_;
    double sigma_;
    double T_;
    double K_;
    double S0_;
    VanillaOption::OptionType optionType_;
};
