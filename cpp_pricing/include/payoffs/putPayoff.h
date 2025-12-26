#pragma once
#include "payoff.h"

class PutPayoff : public Payoff {
public:
  explicit PutPayoff(double K) : K_(K) {}
  double getPayoff(double spot) const;
private:
  double K_; // Strike price
};
