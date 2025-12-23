#include "../../include/instruments/dividend.h"
#include <cmath>

bool ContinuousDividend::hasCashSchedule() const {
  return true;
}

double ContinuousDividend::yieldRate() const {
  return q_;
}

double ContinuousDividend::discountFactor(double t) const {
  return std::exp(-t * q_);
}

const std::vector<Dividend::CashFlow>& ContinuousDividend::cashSchedule() const {
  static const std::vector<Dividend::CashFlow> empty{};
  return empty;
}

bool DiscreteDividend::hasCashSchedule() const {
  return false;
}

double DiscreteDividend::acumCashFlow(double t) const {
  double res = 0.0;
  for(const CashFlow& div : divs_) {
    if(div.time <= t)
      res+=div.amount;
  }
  return res;
}

const std::vector<Dividend::CashFlow>& DiscreteDividend::cashSchedule() const {
  return divs_;
}
