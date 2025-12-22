#pragma once

#include "exercise.h"

class AmericanExercise : public Exercise {
public:
  AmericanExercise(double T) : maturity_{T} {}
  bool canExercise(double t) const override;
  double maturity() const override;
private:
  double maturity_;
};
