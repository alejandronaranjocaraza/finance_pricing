#include "../include/geometricBrownian.h"

#include <cmath>
#include <random>
#include <stdexcept>

std::vector<std::vector<double>> geometricBrownian(
    double S0,
    double T,
    double r,
    double sigma,
    size_t nPaths,
    size_t nSteps
    ) {
  if (S0 < 0.0)
    throw std::invalid_argument("S0 must be greater than or equal to zero.");
  if (T < 0.0)
    throw std::invalid_argument("T must be greater than or equal to zero.");
  if (r < 0.0)
    throw std::invalid_argument("Return (r) must be greater than or equal to zero.");
  if (sigma < 0.0)
    throw std::invalid_argument("Volatility must be greater than or equal to zero.");
  if (nPaths < 1)
    throw std::invalid_argument("At least 1 path must be generated.");
  if (nSteps < 1)
    throw std::invalid_argument("Algorithm requires at least 1 step.");


  double dt = T/nSteps;
  double sqrt_dt = std::sqrt(dt);
  std::random_device rd{};
  std::mt19937 gen{rd()};
  std::normal_distribution<double> normal{0.0, 1.0};
  std::vector<std::vector<double>> res(nPaths,std::vector<double>(nSteps+1,0.0));
  for (size_t i=0; i<nPaths; i++)
    res[i][0] = S0;
  double drift = std::exp((r-sigma*sigma/2)*dt);
  double diffusion;
  double eps;
  for (size_t i=0; i<nPaths; i++) {
    for (size_t j=1; j<nSteps+1; j++) {
      eps = normal(gen);
      diffusion = std::exp(sigma * eps * sqrt_dt);
      res[i][j] = res[i][j-1] * drift * diffusion;
    }
  }
  return res;
}
