#include "../../include/payoffs/callPayoff.h"
#include <algorithm>

double CallPayoff::getPayoff(
    const Option& option, 
    double spot
  ) const {
  return std::max(spot - option.strikePrice(), 0.0);
}
