#include "../../include/exercise/europeanExercise.h"
#include <cmath>

double EuropeanExercise::maturity() const {
  return maturity_;
}

bool EuropeanExercise::canExercise(double t) const {
  return (std::abs(maturity_ - t) < 1e-12) ? true : false;
}
