#include <memory>
#include "buildBinomial.h"
#include "../include/models/binomial.h"
#include "../include/instruments/vanillaOption.h"

std::shared_ptr<BinomialModel<>> makeBinomial(
    std::shared_ptr<const VanillaOption> optionPtr,
    std::shared_ptr<const Stock> stockPtr,
    double r,
    double sigma,
    int n
    ) {
  auto binomial = std::make_shared<BinomialModel<>>(
      optionPtr,
      stockPtr,
      r,
      sigma,
      n
      );
  return binomial;
}
