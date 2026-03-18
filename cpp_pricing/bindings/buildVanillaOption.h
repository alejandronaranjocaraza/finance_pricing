#pragma once

#include <memory>

class VanillaOption;

std::shared_ptr<VanillaOption> makeVanillaOption(
    double strike,
    double maturity,
    char optionType='p',
    char exerciseType='e'
);
