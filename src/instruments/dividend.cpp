#include "../../include/instruments/dividend.h"
#include <cmath>

double ContinuousDividend::yieldRate() const {
  return q;
}

double ContinuousDividend::discountFactor(double t_) const {
  return std::exp(-t_ * q);
}

double DiscreteDividend::acumCashFlow(double t_) const {
  double res = 0.0;
  for(const Dividend& div : divs) {
    if(div.time <= t_)
      res+=div.amount;
  }
  return res;
}
