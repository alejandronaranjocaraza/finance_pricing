#pragma once

#include "../../include/instruments/option.h"
#include "../../include/instruments/stock.h"
#include "parameterization.h"
#include <cmath>
#include <memory>
#include <vector>

template <typename Param = CRR>
class BinomialModel {
public:
  BinomialModel(
      std::shared_ptr<const Option> optionPtr,
      std::shared_ptr<const Stock> stockPtr,
      double r,
      double sigma,
      int n = 100
      ) :
    optionPtr_{std::move(optionPtr)},
    stockPtr_{std::move(stockPtr)},
    params_{makeParams(optionPtr, stockPtr, r, sigma, n)},
    n_{n}
  {}

  double getPrice() const {

    std::vector<double> nodes(n_+1);

    // Terminal Values
    for(int i=0; i <= n_; i++) {
      double ST = (stockPtr_->spot()) * (std::pow(params_.u,i)) * (std::pow(params_.d, n_-i));
      nodes[i] = optionPtr_->getPayoff(ST);
    }

    // Backwards Induction
    for(int i=n_-1; i>=0; i--) {
      for(int j=0; j<=i; j++) {
        nodes[j] = params_.discount * (params_.p * nodes[j+1] + (1-params_.p) * nodes[j]);
      }
    }
    
    return nodes[0];

  }

private:
  struct PricingParams {
    double u;
    double d;
    double p;
    double dt;
    double discount;
  };
  static PricingParams makeParams(
      std::shared_ptr<const Option> optionPtr,
      std::shared_ptr<const Stock> stockPtr,
      double r,
      double sigma,
      int n
      ) {
    double T = optionPtr->exercise().maturity();
    double dt = T/n;
    double q = stockPtr->dividends().yieldRate();
    double a = std::exp((r-q)*dt);
    double u =  Param::u(sigma, dt);
    double d = Param::d(sigma, dt);
    double p = Param::p(a, u, d);
    PricingParams params{u, d, p, dt, std::exp(-dt*r)};
    return params;
  }
  std::shared_ptr<const Option> optionPtr_;
  std::shared_ptr<const Stock> stockPtr_;
  const PricingParams params_;
  int n_;
};
