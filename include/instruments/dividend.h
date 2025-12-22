#pragma once
#include "instrument.h"
#include <vector>

class Dividend {
public:
  virtual ~Dividend() = default;
  virtual double yieldRate() const = 0;
  virtual double discountFactor(double t_) const = 0;
  virtual double acumCashFlow(double t_) const = 0;
private:
};

class ContinuousDividend : public Dividend {
public:
  explicit ContinuousDividend(
      double q_
      ) : q{q_} {}
  double yieldRate() const override;
  double discountFactor(double t_) const override;
  double acumCashFlow(double t_) const override;
private:
  double q;
};

class DiscreteDividend: public Dividend {
public:
  struct Dividend {
    double time;
    double amount;
  };
  DiscreteDividend(std::vector<Dividend> divs_) :
    divs{divs_} {}
  double discountFactor(double t_) const override;
  double acumCashFlow(double t_) const override;
private:
  std::vector<Dividend> divs;
};
