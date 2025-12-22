#pragma once
#include <memory>
#include <stdexcept>
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
  static std::shared_ptr<Payoff> buildPayoff(char type_, double K_) {
    switch (type_) {
      case 'c': return std::make_shared<CallPayoff>(K_);
      case 'p': return std::make_shared<PutPayoff>(K_);
      default: throw std::invalid_argument("Unknown type");
    }

  }
};
