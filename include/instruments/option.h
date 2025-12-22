#pragma once
#include <memory>
#include "instrument.h"
#include "../exercise/exercise.h"
class Payoff;

class Option : public Instrument {
public:
  Option(
      std::shared_ptr<Exercise> exercisePtr_,
      std::shared_ptr<Payoff> payoffPtr_
      ) : exercisePtr{exercisePtr_}, payoffPtr{payoffPtr_} {}
  
  const Payoff& payoff() const;
  const Exercise& exercise() const;
  double getPayoff(double K_) const;
  bool canExercise(double T_) const;
 
private:
    std::shared_ptr<Exercise> exercisePtr;
    std::shared_ptr<Payoff> payoffPtr;
};
