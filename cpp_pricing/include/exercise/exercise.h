#pragma once

class Exercise {
public:
  virtual ~Exercise() = default;
  virtual bool canExercise(double t) const = 0;
  virtual double maturity() const = 0;
};
