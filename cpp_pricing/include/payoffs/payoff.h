#pragma once

class Option;

class Payoff {
public:
  virtual ~Payoff() = default;
  virtual double getPayoff(
      const Option& option,
      double spot
      ) const = 0;
};
