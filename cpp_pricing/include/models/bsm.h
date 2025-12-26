#pragma once

#include "../../include/instruments/option.h"
#include "../../include/instruments/stock.h"

#include <memory>
#include <cmath>

class BSM {
public:
  BSM(
      std::shared_ptr<const Option> optionPtr,
      std::shared_ptr<const Stock> stockPtr,
      double r,
      double sigma
      ) :
    optionPtr_{std::move(optionPtr)},
    stockPtr_{std::move(stockPtr)},
    r_{r},
    sigma_{sigma}
  {}

  double getPrice() {
    double d1 = std::log(stockPtr_->spot() / optionPtr_->payoff());
  }
private:
    struct PricingParams {
      double sigma;
    };
    std::shared_ptr<const Option> optionPtr_;
    std::shared_ptr<const Stock> stockPtr_;
    double r_;
    double sigma_;
    const PricingParams params_;
};
