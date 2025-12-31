#pragma once
#include <memory>
#include "option.h"
#include "../exercise/americanExercise.h"

class Payoff;

class AmericanOption : public Option {
public:
  AmericanOption(
      char type,
      double K,
      double T
      ) : Option(
        K,
        T,
        std::make_shared<AmericanExercise>(),
        buildPayoff(type)
        ) {}
  
private:
  static std::shared_ptr<Payoff> buildPayoff(char type);
};
