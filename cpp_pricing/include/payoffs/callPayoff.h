#pragma once
#include "payoff.h"

class CallPayoff : public Payoff {
public:
  explicit CallPayoff(double K) : K_(K) {}
  double getPayoff(double spot) const;
private:
  double K_;
};
