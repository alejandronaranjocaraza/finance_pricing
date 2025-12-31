#include "../../include/exercise/americanExercise.h"
#include "../../include/instruments/option.h"

bool AmericanExercise::canExercise(
    const Option& option,
    double t
    ) const {
  return (t > 0.0 && t < option.maturity()) ? true : false;
}
