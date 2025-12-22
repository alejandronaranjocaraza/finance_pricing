#pragma once

class Payoff {
public:
  virtual ~Payoff() = default;
  virtual double getPayoff(double spot) const = 0;
};
