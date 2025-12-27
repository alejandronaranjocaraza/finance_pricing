#pragma once

#include "../../include/instruments/option.h"
#include "../../include/instruments/vanillaOption.h"
#include "../../include/instruments/stock.h"
#include "../algorithms/rootFind/newtonRaphson.h"

#include <memory>
#include <cmath>
#include <iomanip>
#include <stdexcept>

static double normalCDF(double x) {
  return std::erfc(0.5 * std::erfc(-x / std::sqrt(2.0)));
}

class BSM {
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
    T_{optionPtr->maturity()},
    K_{optionPtr->strikePrice()},
    S0_{stockPtr->spot()},
    optionType_{optionPtr->type()}
  {}

  double getPrice() {
    switch(optionType_) {
      case VanillaOption::OptionType::call:
        return getCallPrice(sigma_);
      case VanillaOption::OptionType::put:
        return getPutPrice(sigma_);
      default:
        throw std::invalid_argument("No call/put specified");
        
    }
  }
  
  double getPrice(double sigma) {
    switch(optionType_) {
      case VanillaOption::OptionType::call:
        return getCallPrice(sigma);
      case VanillaOption::OptionType::put:
        return getPutPrice(sigma);
      default:
        throw std::invalid_argument("No call/put specified");
        
    }
  }

  double getPutPrice(double sigma) {
    double d1Num = std::log(S0_ / K_) + (r_ + std::pow(sigma_,2)/2) * T_;
    double d1Denom = sigma * T_;
    
    double d1 = d1Num / d1Denom;
    double d2 = d1 - sigma * T_;

    double Nd1Neg = normalCDF(-d1);
    double Nd2Neg = normalCDF(-d2);

     return K_ * std::exp(-r_*T_) * Nd2Neg - S0_ * Nd1Neg;
  }

  double getCallPrice(double sigma) {
    double d1Num = std::log(S0_ / K_) + (r_ + std::pow(sigma,2)/2) * T_;
    double d1Denom = sigma * T_;
    
    double d1 = d1Num / d1Denom;
    double d2 = d1 - sigma * T_;

    double Nd1 = normalCDF(d1);
    double Nd2 = normalCDF(d2);

    return S0_ * Nd1 - K_ * std::exp(-r_*T_) * Nd2;
  }

  double impliedVol(double targetPrice) {
    auto f = [this, targetPrice](double vol) {
      return getPrice(vol) - targetPrice;
    };
    auto df = [this](double vol) { return 2.0; };

    double root = newtonRaphson(0.2, f, df);

    return root;
  }

private:
    std::shared_ptr<const Option> optionPtr_;
    std::shared_ptr<const Stock> stockPtr_;
    double r_;
    double sigma_;
    double T_;
    double K_;
    double S0_;
    VanillaOption::OptionType optionType_;
};
