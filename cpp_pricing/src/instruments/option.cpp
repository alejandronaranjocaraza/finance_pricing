#include "../../include/instruments/option.h"
#include "../../include/exercise/exercise.h"
#include "../../include/payoffs/payoff.h"

const Payoff& Option::payoff() const {
  return *payoffPtr_;
}

const Exercise& Option::exercise() const {
  return *exercisePtr_;
}

double Option::strikePrice() const {
  return K_;
}

double Option::maturity() const {
  return T_;
}

double Option::getPayoff(double spot) const {
  return payoffPtr_->getPayoff(*this, spot);
}

bool Option::canExercise(double t) const {
  return exercisePtr_->canExercise(*this,t);
}
