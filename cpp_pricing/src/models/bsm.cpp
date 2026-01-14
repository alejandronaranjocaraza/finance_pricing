#include "../../include/models/bsm.h"

#include <memory>
#include <cmath>
#include <iomanip>
#include <stdexcept>
#include <numbers>

static double normalCDF(double x) {
  return 0.5 * std::erfc(-x / std::sqrt(2.0));
}

static double normalPDF(double x) {
  return (1/std::sqrt(M_PI * 2))*std::exp(-x*x/2);
}

double BSM::getD1(double sigma) const {
  double d1Num = std::log(S0_ / K_) + (r_ + std::pow(sigma_,2)/2) * T_;
  double d1Denom = sigma * T_;
  
  double d1 = d1Num / d1Denom;
  return d1;
}

double BSM::getD2(double sigma) const {
  double d1 = getD1(sigma);
  double d2 = d1 - sigma * T_;
  return d2;
}

double BSM::getPrice() const {
  switch(optionType_) {
    case VanillaOption::OptionType::call:
      return getCallPrice(sigma_);
    case VanillaOption::OptionType::put:
      return getPutPrice(sigma_);
    default:
      throw std::invalid_argument("No call/put specified");
      
  }
}

double BSM::getPrice(double sigma) {
  switch(optionType_) {
    case VanillaOption::OptionType::call:
      return getCallPrice(sigma);
    case VanillaOption::OptionType::put:
      return getPutPrice(sigma);
    default:
      throw std::invalid_argument("No call/put specified");
      
  }
}

double BSM::getPutPrice(double sigma) const {
  double d1 = getD1(sigma);
  double d2 = getD2(sigma);

  double Nd1Neg = normalCDF(-d1);
  double Nd2Neg = normalCDF(-d2);

   return K_ * std::exp(-r_*T_) * Nd2Neg - S0_ * Nd1Neg;
}

double BSM::getCallPrice(double sigma) const {
  double d1 = getD1(sigma);
  double d2 = getD2(sigma);

  double Nd1 = normalCDF(d1);
  double Nd2 = normalCDF(d2);

  return S0_ * Nd1 - K_ * std::exp(-r_*T_) * Nd2;
}

Greeks BSM::greeks() {
  return Greeks(this);
}

double BSM::impliedVol(double targetPrice) {
  auto f = [this, targetPrice](double vol) {
    return getPrice(vol) - targetPrice;
  };
  auto df = [this](double vol) {
    return greeks().vega(vol);
  };

  double root = newtonRaphson(0.2, f, df);

  return root;
}

double Greeks::delta(double sigma) const {
  double Delta;
  double d1 = bsm->getD1(sigma);
  if(bsm->optionType_ == VanillaOption::OptionType::call) {
    Delta = normalCDF(d1);
  }
  else {
    Delta = normalCDF(d1);
  }
  return Delta;
}

double Greeks::theta(double sigma) const {
  double Theta;
  double d1 = bsm->getD1(sigma);
  double d2 = bsm->getD2(sigma);
  double left = (bsm->S0_ * normalPDF(d1) * bsm->sigma_) / (2 * std::sqrt(bsm->T_));
  double right = bsm->r_ * bsm->K_ * std::exp(-bsm->r_ * bsm->T_);
  if(bsm->optionType_ == VanillaOption::OptionType::call) {
    Theta = -left - right * normalPDF(d2);
  }
  else {
    Theta = -left + right * normalPDF(-d2);
  }
  return Theta;
}

double Greeks::gamma(double sigma) const {
  double d1 = bsm->getD1(sigma);
  return normalPDF(d1) / (bsm->S0_ * sigma * std::sqrt(bsm->T_));
}

double Greeks::vega(double sigma) const {
  double d1 = bsm->getD1(sigma);
  return bsm->S0_ * std::sqrt(bsm->T_) * normalPDF(d1);
}
