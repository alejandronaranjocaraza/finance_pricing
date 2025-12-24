#include "../include/instruments/option.h"
#include "../include/exercise/americanExercise.h"
#include "../include/payoffs/callPayoff.h"
#include "../include/instruments/americanOption.h"
#include <memory>
#include <iostream>

int main() {
  double K = 30; // Strike price
  double T = 2; // Maturity
  double S0 = 100;
  double r = 0.02;
  auto exercise = std::make_shared<AmericanExercise>(1.0); // T = 1 year
  auto payoff   = std::make_shared<CallPayoff>(100.0);     // K = 100

  Option ameCall(exercise, payoff);
  double pay = ameCall.payoff().getPayoff(200);
  std::cout << pay << std::endl;

  AmericanOption amerOpt('c',40.0,2.0);
  std::cout << amerOpt.canExercise(3.0) << std::endl;
  std::cout << amerOpt.canExercise(1.5) << std::endl;
  std::cout << amerOpt.getPayoff(50) << std::endl;

}
