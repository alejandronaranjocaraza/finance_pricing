#pragma once
#include "payoff.h"

class CallPayoff : public Payoff {
public:
  explicit CallPayoff(double K_) : K(K_) {}
  double getPayoff(double spot) const;
private:
  double K;
};
