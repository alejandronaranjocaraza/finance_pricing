#include <memory>
#include "buildBSM.h"
#include "../include/models/bsm.h"

std::shared_ptr<BSM> makeBSM(
    std::shared_ptr<VanillaOption> optionPtr,
    std::shared_ptr<Stock> stockPtr,
    double r,
    double sigma
    ) {
  auto bsm = std::make_shared<BSM>(
      optionPtr,
      stockPtr,
      r,
      sigma
      );
  return bsm;
}
