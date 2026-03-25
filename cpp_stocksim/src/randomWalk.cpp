#include <cmath>
#include <random>
#include <stdexcept>

#include "../include/randomWalk.h"

std::vector <std::vector<double>> randomWalk(
    double S0,
    double T,
    double r,
    double sigma,
    size_t nPaths,
    size_t nSteps
    )
{
  double dt = T / nSteps;
  double u = std::exp(sigma * std::sqrt(dt));
  double d = 1 / u;
  double a = std::exp(r * dt);
  double p = (a-d) / (u-d);

  if (p<0 || p> 1) {
    throw std::runtime_error("Invalid p.");
  }

  std::vector<std::vector<double>> res(nPaths,std::vector<double>(nSteps+1,0.0));
  for (size_t i=0; i<nPaths; i++)
    res[i][0] = S0;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::bernoulli_distribution bernoulli(p);
  for (size_t i=0; i<nPaths; i++) {
    for (size_t j=1; j<nSteps+1; j++) {
      bool trial = bernoulli(gen);
      res[i][j] = res[i][j-1] * (trial ? u : d);
    }
  }
  return res;
}
