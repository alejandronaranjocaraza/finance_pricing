#include "../../include/exercise/americanExercise.h"
#include <cmath>

bool AmericanExercise::canExercise(
    const Option& option,
    double t
    ) const {
  return (t > 0.0 && t < option.maturity()) ? true : false;
}
