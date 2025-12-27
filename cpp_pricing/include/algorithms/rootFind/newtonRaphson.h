#pragma once

#include <cmath>

template <typename Function, typename Gradient>
double newtonRaphson(
    double x0,
    const Function& f,
    const Gradient& df,
    double h = 1e-10,
    int n = 1000
    ) {
  double x = x0;
  double fx = f(x);
  double dfx = df(x);
  for(int i=0; i<n; i++) {
    x = x - fx / dfx;
    fx = f(x);
    dfx = df(x);
    if(std::abs(fx) < h)
      return x;
  }
  return x;
}
