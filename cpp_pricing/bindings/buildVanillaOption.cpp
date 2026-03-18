#include <memory>
#include <stdexcept>

#include "buildVanillaOption.h"
#include "../include/instruments/vanillaOption.h"
#include "../include/exercise/europeanExercise.h"
#include "../include/exercise/americanExercise.h"
#include "../include/payoffs/callPayoff.h"
#include "../include/payoffs/putPayoff.h"

std::shared_ptr<VanillaOption> makeVanillaOption(
    double strike,
    double maturity,
    char optionTypeChar,
    char exerciseTypeChar
) {

  VanillaOption::ExerciseType exerciseType;
  VanillaOption::OptionType optionType;

  switch(optionTypeChar) {
    case 'c':
      optionType = VanillaOption::OptionType::call;
      break;
    case 'p':
      optionType = VanillaOption::OptionType::put;
      break;
    default:
      throw std::invalid_argument("Invalid option type input.");
  }

  switch(exerciseTypeChar) {
    case 'a':
      exerciseType = VanillaOption::ExerciseType::american;
      break;
    case 'e':
      exerciseType = VanillaOption::ExerciseType::european;
      break;
    default:
      throw std::invalid_argument("Invalid option exercise type input.");
  }

  
  // VanillaOption::OptionType optType2 = VanillaOption::OptionType::put;
  auto vanillaOptionPtr = std::make_shared<VanillaOption>(
      strike,
      maturity,
      optionType,
      exerciseType
      );

  return vanillaOptionPtr;
};
