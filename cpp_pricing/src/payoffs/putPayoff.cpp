#include "../../include/payoffs/putPayoff.h"
#include <algorithm>

double PutPayoff::getPayoff(double spot) const {
  return std::max(K_ - spot, 0.0);
}
