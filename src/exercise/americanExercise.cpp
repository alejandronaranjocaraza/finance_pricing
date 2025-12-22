#include "../../include/exercise/americanExercise.h"
#include <cmath>

double AmericanExercise::maturity() const {
  return maturity_;
}

bool AmericanExercise::canExercise(double t) const {
  return (t > 0.0 && t < maturity_) ? true : false;
}
