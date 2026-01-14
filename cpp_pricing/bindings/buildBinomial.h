#pragma once

#include <memory>
#include "../include/models/binomial.h"

class VanillaOption;
class Stock;

std::shared_ptr<BinomialModel<>> makeBinomial(
    std::shared_ptr<const VanillaOption> optionPtr,
    std::shared_ptr<const Stock> stockPtr,
    double r,
    double sigma
    );
