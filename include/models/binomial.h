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
    params_{makeParams(
        optionPtr->exercise().maturity(),
        stockPtr->dividends().yieldRate(),
        r,
        sigma,
        n
        )},
    n_{n}
  {}
  
  double getPriceDividendCashSchedule() const {

    if(!stockPtr_->dividends().hasCashSchedule()) {
      std::vector<std::vector<double>> SAdj(
          params_.n+1,
          std::vector<double>(params_.n+1,0.0)
          );
      double SAdj0=stockPtr_->spot();
      for(auto div : stockPtr_->dividends().cashSchedule()) {
        SAdj0-=div.amount * std::exp(-params_.r*(div.time));
      }
      for(int i=0; i<=params_.n; i++) {
        for(int j=0; j<=params_.n; j++) {
          double St = (stockPtr_->spot()) * (std::pow(params_.u,i-j)) * (std::pow(params_.d, i-j));
          for(auto div : stockPtr_->dividends().cashSchedule()) {
            if(div.time < i*params_.dt) {
              SAdj[i][j]=St-div.amount*std::exp(-params_.r*(div.time-i*params_.dt));
            }
          }

        }
      } 
    }
  }
  
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
        double continuation = params_.discount * (params_.p * nodes[j+1] + (1-params_.p) * nodes[j]);
        if (optionPtr_->canExercise(i * params_.dt)) {
          double St = (stockPtr_->spot()) * (std::pow(params_.u,i-j)) * (std::pow(params_.d, i-j));
          double early = optionPtr_->getPayoff(St);
          nodes[j] = std::max(early, continuation);
        }
        else
          nodes[i] = continuation;
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
      double T,
      double q,
      double r,
      double sigma,
      int n
      ) {
    double dt = T/n;
    double a = std::exp((r-q)*dt);
    double u =  Param::u(sigma, dt);
    double d = Param::d(sigma, dt);
    double p = Param::p(a, u, d);
    double discount = std::exp(-dt*r);
    PricingParams params{u, d, p, dt, discount};
    return params;
  }
  std::shared_ptr<const Option> optionPtr_;
  std::shared_ptr<const Stock> stockPtr_;
  const PricingParams params_;
  int n_;
};
