#pragma once

#include "exercise.h"
#include "../instruments/option.h"

class EuropeanExercise : public Exercise {
public:
  EuropeanExercise()=default;
  bool canExercise(
      const Option& option,
      double t
      ) const override;
};
