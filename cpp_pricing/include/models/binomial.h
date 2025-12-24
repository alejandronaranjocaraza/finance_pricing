#pragma once

#include "../../include/instruments/option.h"
#include "../../include/instruments/stock.h"
#include "parameterization.h"

#include <cmath>
#include <memory>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <utility>

// For personal IDE-related reasons, .h and .tpp are included in
// same file (single .h). This can easily be refractored into
// seperate files.

// .H

template <typename Param = CRR>
class BinomialModel {
public:
  BinomialModel(
      std::shared_ptr<const Option> optionPtr,
      std::shared_ptr<const Stock> stockPtr,
      double r,
      double sigma,
      int n = 100
      );

  double getPrice() const;
 
  // Get Option Price where unerlying stock has discrete dividend cash schedule
  double getPriceDS() const;

  // Get Option Price where underlying stock has continuous dividend yield
  double getPriceCY() const;

private:
  struct PricingParams {
    double u;
    double d;
    double p;
    double r;
    double dt;
    int n;
    double discount;
  };
  static PricingParams makeParams(
      double T,
      double q,
      double r,
      double sigma,
      int n
      );
  std::shared_ptr<const Option> optionPtr_;
  std::shared_ptr<const Stock> stockPtr_;
  const PricingParams params_;
};

// .TPP

template <typename Param>
BinomialModel<Param>::BinomialModel(
      std::shared_ptr<const Option> optionPtr,
      std::shared_ptr<const Stock> stockPtr,
      double r,
      double sigma,
      int n
      ) :
    optionPtr_{std::move(optionPtr)},
    stockPtr_{std::move(stockPtr)},
    params_{makeParams(
        optionPtr_->exercise().maturity(),
        stockPtr_->dividends().yieldRate(),
        r,
        sigma,
        n
        )} {}

template <typename Param>
double BinomialModel<Param>::getPrice() const {
  if(stockPtr_->dividends().hasCashSchedule())
    return getPriceDS();
  else if(stockPtr_->dividends().hasContinuousYield())
    return getPriceCY();
  else
    throw std::logic_error("Underlying stock dividends not supported");
}

template <typename Param>
double BinomialModel<Param>::getPriceDS() const {

  const auto& divSchedule = stockPtr_->dividends().cashSchedule();

  // Build Price matrix
  std::vector<std::vector<double>> S(
      params_.n+1,
      std::vector<double>(params_.n+1,0.0)
      );
  std::vector<double> nodes(params_.n+1);

  // Get S* present value
  double SAdj0=stockPtr_->spot();
  for(const auto& div : divSchedule) {
    SAdj0 -= div.amount * std::exp(-params_.r*(div.time));
  }

  // Build binomial tree
  for(int i=0; i<=params_.n; i++) {
    double tau = params_.dt * i;
    for(int j=0; j<=i; j++) {
      double SAdj = (SAdj0) * (std::pow(params_.u,j)) * (std::pow(params_.d, i-j));
      double St = SAdj;
      for(const auto& div : divSchedule) {

        // Consider Dividend payments are before div.time(ex-dividend dates)
        if(tau< div.time) {
          St += div.amount*std::exp(-params_.r*(div.time-i*params_.dt));
        }
      }
      S[i][j] = St;
    }
  }
  
  // Set terminal values
  for(int j=0; j<=params_.n; j++)
    nodes[j] = optionPtr_->getPayoff(S[params_.n][j]);

  // Backwards induction
  for(int i=params_.n-1; i>=0; i--) {
    double tau = i*params_.dt;
    for(int j=0; j<=i; j++) {
      double continuation = params_.discount * (params_.p * nodes[j+1] + (1-params_.p) * nodes[j]);
      if (optionPtr_->canExercise(tau)) {
        double St = S[i][j];
        double early = optionPtr_->getPayoff(St);
        nodes[j] = std::max(early, continuation);
      }
      else
        nodes[j] = continuation;
    }
  }

  // Return first node
  return nodes[0];
}

template <typename Param>
double BinomialModel<Param>::getPriceCY() const {

  std::vector<double> nodes(params_.n+1);

  // Terminal Values
  for(int i=0; i <= params_.n; i++) {
    double ST = (stockPtr_->spot()) * (std::pow(params_.u,i)) * (std::pow(params_.d, params_.n-i));
    nodes[i] = optionPtr_->getPayoff(ST);
  }

  // Backwards Induction
  for(int i=params_.n-1; i>=0; i--) {
    for(int j=0; j<=i; j++) {
      double continuation = params_.discount * (params_.p * nodes[j+1] + (1-params_.p) * nodes[j]);
      if (optionPtr_->canExercise(i * params_.dt)) {
        double St = (stockPtr_->spot()) * (std::pow(params_.u,j)) * (std::pow(params_.d, i-j));
        double early = optionPtr_->getPayoff(St);
        nodes[j] = std::max(early, continuation);
      }
      else
        nodes[j] = continuation;
    }
  }
  
  return nodes[0];
}

template <typename Param>
typename BinomialModel<Param>::PricingParams
BinomialModel<Param>::makeParams(
    double T,
    double q,
    double r,
    double sigma,
    int n
    ) {
  if(n<=0)
    throw std::invalid_argument("n must be larger than 0");
  double dt = T/n;
  double a = std::exp((r-q)*dt);
  double u =  Param::u(sigma, dt);
  double d = Param::d(sigma, dt);
  double p = Param::p(a, u, d);
  double discount = std::exp(-dt*r);
  PricingParams params{u, d, p, r, dt, n, discount};
  return params;
}
