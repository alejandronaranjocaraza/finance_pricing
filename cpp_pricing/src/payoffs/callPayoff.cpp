#include "../../include/payoffs/callPayoff.h"
#include <algorithm>

double CallPayoff::getPayoff(double spot) const {
  return std::max(spot - K_, 0.0);
}
