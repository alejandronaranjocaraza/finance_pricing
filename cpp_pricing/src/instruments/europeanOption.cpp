#include <stdexcept>
#include "../../include/instruments/europeanOption.h"

std::shared_ptr<Payoff>
EuropeanOption::buildPayoff(char type) {
  switch (type) {
    case 'c': return std::make_shared<CallPayoff>();
    case 'p': return std::make_shared<PutPayoff>();
    default: throw std::invalid_argument("Unknown type");
  }
}
