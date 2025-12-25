#pragma once
#include <memory>
#include "option.h"
#include "../exercise/europeanExercise.h"
#include "../payoffs/callPayoff.h"
#include "../payoffs/putPayoff.h"

class EuropeanOption : public Option {
public:
  EuropeanOption(
      char type_,
      double K_,
      double T_
      ) : Option(
        std::make_shared<EuropeanExercise>(T_),
        buildPayoff(type_, K_)
        ) {}
  
private:
  static std::shared_ptr<Payoff> buildPayoff(char type_, double K_);
};
