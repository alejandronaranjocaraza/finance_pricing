#include "../../include/instruments/vanillaOption.h"

#include <stdexcept>

VanillaOption::VanillaOption(
    double K,
    double T,
    OptionType optionType,
    ExerciseType exerciseType)
    : optionType_{optionType},
      exerciseType_{exerciseType},
      Option(
          K,
          T,
          (exerciseType == ExerciseType::european)
            ? std::shared_ptr<Exercise>(std::make_shared<EuropeanExercise>())
            : std::shared_ptr<Exercise>(std::make_shared<AmericanExercise>()),
          (optionType == OptionType::call)
            ? std::shared_ptr<Payoff>(std::make_shared<CallPayoff>())
            : std::shared_ptr<Payoff>(std::make_shared<PutPayoff>()))
    {
  }

VanillaOption::OptionType
VanillaOption::optionType() const {
  return optionType_;
}

VanillaOption::ExerciseType
VanillaOption::exerciseType() const {
  return exerciseType_;
}
