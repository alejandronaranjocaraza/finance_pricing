#pragma once

#include "exercise.h"

class Option;

class AmericanExercise : public Exercise {
public:
  AmericanExercise()=default;
  bool canExercise(
      const Option& option,
      double t
      ) const override;
};
