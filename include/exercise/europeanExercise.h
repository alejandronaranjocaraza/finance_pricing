#pragma once

#include "exercise.h"

class EuropeanExercise : public Exercise {
public:
  EuropeanExercise(double T) : maturity_{T} {}
  double maturity() const override;
  bool canExercise(double t) const override;
private:
  double maturity_;
};
