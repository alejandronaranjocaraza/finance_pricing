#include "../../include/exercise/europeanExercise.h"
#include <cmath>

bool EuropeanExercise::canExercise(
    const Option& option,
    double t
    ) const {
  return (std::abs(option.maturity() - t) < 1e-12) ? true : false;
}
