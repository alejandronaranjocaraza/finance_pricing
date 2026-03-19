#include "../../include/models/bsm.h"

#include <memory>
#include <cmath>
#include <limits>
#include <iomanip>
#include <stdexcept>
#include <numbers>

static double normalCDF(double x) {
  return 0.5 * std::erfc(-x / std::sqrt(2.0));
}

static double normalPDF(double x) {
  return (1/std::sqrt(M_PI * 2))*std::exp(-x*x/2);
}

BSM::BSM(
    std::shared_ptr<const VanillaOption> optionPtr,
    std::shared_ptr<const Stock> stockPtr,
    double r,
    double sigma
    ) :
  optionPtr_{std::move(optionPtr)},
  stockPtr_{std::move(stockPtr)},
  r_{r},
  q_{stockPtr_->dividends().yieldRate()},
  sigma_{sigma},
  T_{optionPtr_->maturity()},
  K_{optionPtr_->strikePrice()},
  S0_{stockPtr_->spot()},
  optionType_{optionPtr_->optionType()}
{
  if (optionPtr_->exerciseType() == VanillaOption::ExerciseType::american) {
    throw std::invalid_argument("BSM model does not take american options.");
  }
}

double BSM::getD1(double sigma) const {
  double d1Num = std::log(S0_ / K_) + (r_ - q_ + 0.5 * (sigma * sigma)) * T_;
  double d1Denom = sigma * std::sqrt(T_);
  
  double d1 = d1Num / d1Denom;
  return d1;
}

double BSM::getD2(double sigma) const {
  double d1 = getD1(sigma);
  double d2 = d1 - sigma * std::sqrt(T_);
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

double BSM::getPrice(double sigma) const {
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

   return K_ * std::exp(-r_*T_) * Nd2Neg - S0_ * std::exp(-q_*T_) * Nd1Neg;
}

double BSM::getCallPrice(double sigma) const {
  double d1 = getD1(sigma);
  double d2 = getD2(sigma);

  double Nd1 = normalCDF(d1);
  double Nd2 = normalCDF(d2);

  return S0_ * std::exp(-q_*T_) * Nd1 - K_ * std::exp(-r_*T_) * Nd2;
}

Greeks BSM::greeks() const {
  return Greeks(this);
}

double BSM::impliedVol(double targetPrice) {
  double lower;
  double upper;

  switch(optionType_) {
    case VanillaOption::OptionType::call:
      lower = std::max(0.0, S0_ * std::exp(-q_*T_) - K_ * std::exp(-r_*T_));
      upper = S0_ * std::exp(-q_ * T_);
      break;
    case VanillaOption::OptionType::put:
      lower = std::max(0.0, K_ * std::exp(-r_*T_) - S0_ * std::exp(-q_*T_));
      upper = K_ * std::exp(-r_ * T_);
      break;
    default:
      throw std::invalid_argument("No call/put specified");
  }

  if (targetPrice < lower || targetPrice > upper)
    return std::numeric_limits<double>::quiet_NaN();
  auto f = [this, targetPrice](double vol) {
    return getPrice(vol) - targetPrice;
  };

  Greeks g(this);

  auto df = [&g](double vol) {
    return g.vega(vol);
  };

  double volCM = BSM::corradoMiller(targetPrice);

  double root = newtonRaphson(volCM, f, df);

  if (std::isnan(root) || root <= 0.0 || root >5.0)
    root = bisection(1e-6,5.0,f);

  return root;
}


double BSM::corradoMiller(double targetPrice) const {
 
  double discountedK = K_ * std::exp(-r_ * T_);
  double discountedS = S0_ * std::exp(-q_ * T_);
  double term1 = targetPrice - (discountedS - discountedK) / 2.0;
  double innerSqrt = std::pow(term1, 2) - std::pow(discountedS - discountedK, 2) / M_PI;
    
  if (innerSqrt < 0) innerSqrt = 0;
  
  double numerator = std::sqrt(2.0 * M_PI) / (discountedS + discountedK) * (term1 + std::sqrt(innerSqrt));
  
  return numerator / std::sqrt(T_);
}



double Greeks::delta(double sigma) const {
  double Delta;
  double d1 = bsm->getD1(sigma);
  double factor = std::exp(-bsm->q_ * bsm->T_);
  if(bsm->optionType_ == VanillaOption::OptionType::call) {
    Delta = factor * normalCDF(d1);
  }
  else {
    Delta = factor * (normalCDF(d1) - 1.0);
  }
  return Delta;
}

double Greeks::theta(double sigma) const {
  double Theta;
  double d1 = bsm->getD1(sigma);
  double d2 = bsm->getD2(sigma);
  double left = (bsm->S0_ * std::exp(-bsm->q_ * bsm->T_) * normalPDF(d1) * sigma) / (2 * std::sqrt(bsm->T_));
  double mid = bsm->r_ * bsm->K_ * std::exp(-bsm->r_ * bsm->T_);
  double right = bsm->q_ * bsm->S0_ * std::exp(-bsm->q_ * bsm->T_);
  if(bsm->optionType_ == VanillaOption::OptionType::call) {
    Theta = -left - mid * normalCDF(d2) + right * normalCDF(d1);
  }
  else {
    Theta = -left + mid * normalCDF(-d2) - right * normalCDF(-d1);
  }
  return Theta;
}

double Greeks::gamma(double sigma) const {
  double d1 = bsm->getD1(sigma);
  return std::exp(-bsm->q_ * bsm->T_) * normalPDF(d1) / (bsm->S0_ * sigma * std::sqrt(bsm->T_));
}

double Greeks::vega(double sigma) const {
  double d1 = bsm->getD1(sigma);
  return bsm->S0_ * std::exp(-bsm->q_ * bsm->T_) * std::sqrt(bsm->T_) * normalPDF(d1);
}
