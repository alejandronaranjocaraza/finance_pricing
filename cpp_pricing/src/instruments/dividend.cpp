#include "../../include/instruments/dividend.h"
#include <cmath>

bool ContinuousDividend::hasCashSchedule() const {
  return false;
}

bool ContinuousDividend::hasContinuousYield() const {
  return true;
}

double ContinuousDividend::yieldRate() const {
  return q_;
}

double ContinuousDividend::discountFactor(double t) const {
  return std::exp(-t * q_);
}

double ContinuousDividend::acumCashFlow(double t) const {
  return 0.0;
}

const std::vector<Dividend::CashFlow>& ContinuousDividend::cashSchedule() const {
  static const std::vector<Dividend::CashFlow> empty{};
  return empty;
}

bool DiscreteDividend::hasCashSchedule() const {
  return true;
}

bool DiscreteDividend::hasContinuousYield() const {
  return false;
}

double DiscreteDividend::yieldRate() const {
  return 0.0;
}

double DiscreteDividend::discountFactor(double t) const {
  return 0.0;
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
