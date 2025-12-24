#ifndef BINOMIAL_H
#define BINOMIAL_H

#include <vector>
#include "../options/europeanOption.h"
#include "../options/americanOption.h"
#include "../additional/binomial/parameterization.h"
#include "../additional/dividend.h"

template <typename Param = CRR>
class BINOMIAL {
public:
  BINOMIAL(
    double sigma,
    double r,
    double S0,
    int n,
    double q = 0.0
  );
 
  BINOMIAL(
    double u,
    double d,
    double r,
    double S0,
    int n,
    double q = 0.0
  );

  // European
  double getPrice(
    const EuropeanOption& opt
  ) const;

  // European with dividends
  double getPrice(
    const EuropeanOption& opt,
    const std::vector<Dividend>& div
  ) const;

  // American
  double getPrice(
    const AmericanOption& opt
  ) const;

  // American with dividends
  double getPrice(
    const AmericanOption& opt,
    const std::vector<Dividend>& div
  ) const;

private:
  struct PricingParams {
    double u;
    double d;
    double p;
    double dt;
    double discount;
  };
  PricingParams setPricingParams(double T) const;
  double sigma; // Volatility
  double u; // Stock up factor at each time step
  double d; // Stock down factor at each time step
  double r; // Risk free rate
  double S0; // Initial Stock Price
  int n; // Steps
  double q;
};
//#include "BINOMIAL.tpp"
#endif
