#pragma once
#include <memory>
#include "instrument.h"
#include "../exercise/exercise.h"

class Payoff;

class Option : public Instrument {
public:
  Option(
      double K,
      double T,
      std::shared_ptr<Exercise> exercisePtr,
      std::shared_ptr<Payoff> payoffPtr
      ) :
    K_{K},
    T_{T},
    exercisePtr_{exercisePtr},
    payoffPtr_{payoffPtr} {}
  
  const Payoff& payoff() const;
  const Exercise& exercise() const;
  double strikePrice() const;
  double maturity() const;
  double getPayoff(double spot) const;
  bool canExercise(double t) const;
 
private:
  double K_;
  double T_;
  std::shared_ptr<Exercise> exercisePtr_;
  std::shared_ptr<Payoff> payoffPtr_;
};
