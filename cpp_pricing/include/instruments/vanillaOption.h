#pragma once

#include "option.h"
#include "../exercise/americanExercise.h"
#include "../exercise/europeanExercise.h"
#include "../payoffs/putPayoff.h"
#include "../payoffs/callPayoff.h"

class VanillaOption : public Option {
public:
  enum struct OptionType {
    call,
    put
  };
  enum struct ExerciseType {
    european,
    american
  };
  VanillaOption(
      double K,
      double T,
      OptionType optionType = OptionType::call,
      ExerciseType exerciseType = ExerciseType::european
      //OptionType optionType = OptionType::call,
      //ExerciseType exerciseType = ExerciseType::european
      );

  OptionType optionType() const;
  ExerciseType exerciseType() const;
private:
  OptionType optionType_;
  ExerciseType exerciseType_;
};
