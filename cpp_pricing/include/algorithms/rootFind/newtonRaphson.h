#pragma once

#include <cmath>
#include <limits>
#include <algorithm>

template <typename Function, typename Gradient>
double newtonRaphson(
    double x0,
    const Function& f,
    const Gradient& df,
    double tol = 1e-8,
    double derivTol = 1e-10,
    int n = 1000
    ) {
  double x = x0;
  double fx;
  double dfx;
  for(int i=0; i<n; i++) {

    fx = f(x);

    if (std::abs(fx) < tol)
      return x;

    dfx = df(x);

    if (std::abs(dfx) < derivTol)
      return std::numeric_limits<double>::quiet_NaN();

    double xNext = x - fx /dfx;

    if (!std::isfinite(xNext))
      return std::numeric_limits<double>::quiet_NaN();

    if (std::abs(x-xNext) < tol * std::max(1.0,std::abs(xNext)))
      return xNext;

    x = xNext;
  }
  return std::numeric_limits<double>::quiet_NaN();
}
