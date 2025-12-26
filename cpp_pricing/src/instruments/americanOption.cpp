#include <memory>
#include <stdexcept>
#include "../../include/instruments/americanOption.h"
#include "../../include/payoffs/callPayoff.h"
#include "../../include/payoffs/putPayoff.h"

std::shared_ptr<Payoff>
AmericanOption::buildPayoff(char type) {
  switch (type) {
    case 'c': return std::make_shared<CallPayoff>();
    case 'p': return std::make_shared<PutPayoff>();
    default: throw std::invalid_argument("Unknown type");
  }
}
