#pragma once

#include <cmath>
#include <limits>

template <typename Function>
double bisection(
    double xLow,
    double xHigh,
    const Function& f,
    double tol = 1e-10,
    int n = 1000
    ) {
  double fLow = f(xLow);
  double fHigh = f(xHigh);

  if (std::abs(fLow) < tol)
    return xLow;
  if (std::abs(fHigh) < tol)
    return xHigh;

  if (fLow * fHigh > 0)
    return std::numeric_limits<double>::quiet_NaN();

  for (int i=0; i < n; i++) {
    double xMid = 0.5 * (xLow + xHigh);
    double fMid = f(xMid);

    if (std::abs(fMid) < tol || std::abs(xHigh - xLow) < tol)
      return xMid;

    if (fLow * fMid < 0.0) {
      xHigh = xMid;
      fHigh = fMid;
    }

    else {
      xLow = xMid;
      fLow = fMid;
    }
  }
  return std::numeric_limits<double>::quiet_NaN();
}

