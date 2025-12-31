#pragma once

#include <memory>

class BSM;
class VanillaOption;
class Stock;

std::shared_ptr<BSM> makeBSM(
    std::shared_ptr<VanillaOption> optionPtr,
    std::shared_ptr<Stock> stockPtr,
    double r,
    double sigma
    );
