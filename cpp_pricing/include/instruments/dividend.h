#pragma once
#include "instrument.h"
#include <vector>

class Dividend {
public:
  struct CashFlow {
    double time;
    double amount;
  };
  virtual ~Dividend() = default;
  virtual bool hasCashSchedule() const = 0;
  virtual bool hasContinuousYield() const = 0;
  virtual double yieldRate() const = 0;
  virtual double discountFactor(double t) const = 0;
  virtual double acumCashFlow(double t) const = 0;
  virtual const std::vector<CashFlow>&
    cashSchedule() const = 0;
private:
};

class ContinuousDividend : public Dividend {
public:
  explicit ContinuousDividend(
      double q
      ) : q_{q} {}
  bool hasCashSchedule() const override;
  bool hasContinuousYield() const override;
  double yieldRate() const override;
  double discountFactor(double t) const override;
  double acumCashFlow(double t) const override;
  const std::vector<CashFlow>&
    cashSchedule() const override;
private:
  double q_;
};

class DiscreteDividend: public Dividend {
public:
  DiscreteDividend(std::vector<CashFlow> divs) :
    divs_{std::move(divs)} {}
  bool hasCashSchedule() const override;
  bool hasContinuousYield() const override;
  double yieldRate() const override;
  double discountFactor(double t) const override;
  double acumCashFlow(double t) const override;
  const std::vector<CashFlow>&
    cashSchedule() const override;
private:
  std::vector<CashFlow> divs_;
};
