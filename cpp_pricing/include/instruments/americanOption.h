#pragma once
#include <memory>
#include "option.h"
#include "../exercise/americanExercise.h"
#include "../payoffs/callPayoff.h"
#include "../payoffs/putPayoff.h"

class AmericanOption : public Option {
public:
  AmericanOption(
      char type_,
      double K_,
      double T_
      ) : Option(
        std::make_shared<AmericanExercise>(T_),
        buildPayoff(type_, K_)
        ) {}
  
private:
  static std::shared_ptr<Payoff> buildPayoff(char type_, double K_);
};
