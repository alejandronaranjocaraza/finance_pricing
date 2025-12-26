#pragma once
#include "payoff.h"
#include "../instruments/option.h"

class CallPayoff : public Payoff {
public:
  CallPayoff() = default;
  double getPayoff(
      const Option& option, double spot
    ) const override;
};
