#pragma once
#include <memory>
#include "option.h"
#include "../exercise/americanExercise.h"
#include "../payoffs/callPayoff.h"
#include "../payoffs/putPayoff.h"

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
