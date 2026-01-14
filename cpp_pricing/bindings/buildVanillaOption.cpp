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
    char exerciseType,
    char optionType
) {
  
  std::shared_ptr<Exercise> exercisePtr;
  std::shared_ptr<Payoff> payoffPtr;
  VanillaOption::OptionType tp;

  switch(exerciseType) {
    case 'a':
      exercisePtr  = std::make_shared<AmericanExercise>();
      break;
    case 'e':
      exercisePtr  = std::make_shared<EuropeanExercise>();
      break;
    default:
      throw std::invalid_argument("Invalid exercise input.");
  }

  switch(optionType) {
    case 'c':
      payoffPtr  = std::make_shared<CallPayoff>();
      tp = VanillaOption::OptionType::call;
      break;
    case 'p':
      payoffPtr  = std::make_shared<PutPayoff>();
      tp = VanillaOption::OptionType::put;
      break;
    default:
      throw std::invalid_argument("Invalid optionType input.");
  }
  
  // VanillaOption::OptionType optType2 = VanillaOption::OptionType::put;
  auto vanillaOptPtr = std::make_shared<VanillaOption>(
      strike,
      maturity,
      exercisePtr,
      payoffPtr,
      tp
      );

  return vanillaOptPtr;
};
