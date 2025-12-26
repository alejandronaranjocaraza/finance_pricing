#pragma once

#include "exercise.h"
#include "../instruments/option.h"

class AmericanExercise : public Exercise {
public:
  AmericanExercise()=default;
  bool canExercise(
      const Option& option,
      double t
      ) const override;
};
