#pragma once

#include <vector>

std::vector<std::vector<double>> geometricBrownian(
    double S0,
    double T,
    double r,
    double sigma,
    size_t nPaths=1,
    size_t nSteps=100
    );
