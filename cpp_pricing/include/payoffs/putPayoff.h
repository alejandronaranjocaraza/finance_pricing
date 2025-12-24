#pragma once
#include "payoff.h"

class PutPayoff : public Payoff {
public:
  explicit PutPayoff(double K_) : K(K_) {}
  double getPayoff(double spot) const;
private:
  double K; // Strike price
};
