#pragma once
#include <memory>
#include "option.h"
#include "../exercise/europeanExercise.h"
#include "../payoffs/callPayoff.h"
#include "../payoffs/putPayoff.h"

class EuropeanOption : public Option {
public:
  EuropeanOption(
      char type,
      double K,
      double T
      ) : Option(
        K,
        T,
        std::make_shared<EuropeanExercise>(),
        buildPayoff(type)
        ) {}
  
private:
  static std::shared_ptr<Payoff> buildPayoff(char type);
};
