#include <cmath>
#include "../../include/exercise/europeanExercise.h"
#include "../../include/instruments/option.h"

bool EuropeanExercise::canExercise(
    const Option& option,
    double t
    ) const {
  return (std::abs(option.maturity() - t) < 1e-12) ? true : false;
}
