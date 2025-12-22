#include "../../include/instruments/option.h"
#include "../../include/exercise/exercise.h"
#include "../../include/payoffs/payoff.h"

const Payoff& Option::payoff() const {
  return *payoffPtr;
}

const Exercise& Option::exercise() const {
  return *exercisePtr;
}

double Option::getPayoff(double K_) const {
  return payoffPtr->getPayoff(K_);
}

bool Option::canExercise(double T_) const {
  return exercisePtr->canExercise(T_);
}
