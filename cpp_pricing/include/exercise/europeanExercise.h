#pragma once

#include "exercise.h"

class Option;

class EuropeanExercise : public Exercise {
public:
  EuropeanExercise()=default;
  bool canExercise(
      const Option& option,
      double t
      ) const override;
};
