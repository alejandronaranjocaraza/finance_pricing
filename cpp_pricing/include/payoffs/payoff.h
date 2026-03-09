#pragma once

class Option;

class Payoff {
public:
  virtual ~Payoff() = default;
  virtual double getPayoff(
      const Option& option,
      double spot
      ) const = 0;
  virtual char tag() const = 0;
};
