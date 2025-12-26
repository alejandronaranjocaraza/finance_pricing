#include "../../include/payoffs/putPayoff.h"
#include <algorithm>

double PutPayoff::getPayoff(
    const Option& option,
    double spot) const {
  return std::max(option.strikePrice() - spot, 0.0);
}
