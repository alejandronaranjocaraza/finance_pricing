#include <stdexcept>
#include "../../include/instruments/americanOption.h"

std::shared_ptr<Payoff>
AmericanOption::buildPayoff(char type_, double K_) {
  switch (type_) {
    case 'c': return std::make_shared<CallPayoff>(K_);
    case 'p': return std::make_shared<PutPayoff>(K_);
    default: throw std::invalid_argument("Unknown type");
  }
}
