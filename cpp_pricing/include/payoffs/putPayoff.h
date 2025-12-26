#pragma once
#include "payoff.h"
#include "../instruments/option.h"

class PutPayoff : public Payoff {
public:
  PutPayoff() = default;
  double getPayoff(
      const Option& option, double spot
      ) const override;
};
