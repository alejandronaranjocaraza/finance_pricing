#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>

#define LOG(x) std::cout << x << std::endl;

double payoff(
    double K,
    double St,
    char optType) {
  if (optType == 'c')
    return std::max(St-K,0.0);
  else if (optType == 'p')
    return std::max(K-St,0.0);
  else
    throw std::invalid_argument("Option can only be put ('p') or call ('c').");
}

// Example implementation of binomial tree (backwards induction)
// to determine price of european call option
double binomialPrice(
    double T, // Maturity
    double K, // Strike price
    char optType, // Option type. Can be 'c' (call) or 'p' (put)
    double S0, // Stock current price
    double r, // Risk neutral return
    double u, // Stock up movement
    double d, // Stock down movement
    double n=100 // Iterations / # time steps
    ) {

  if (u==d)
    return payoff(K * std::exp(-r * T),S0,optType);
    
  double dt = T / n; // Time step length
  double discount = std::exp(-dt * r);
  double p = (std::exp(r * dt) - d) / (u - d);
  double ST;
  double FT;

  std::vector<double> nodes(n+1); // Initialize nodes
  for (int i = 0; i<n+1; i++) {
    ST = (std::pow(u,i) * std::pow(d,n-i)) * S0;
    FT = payoff(K,ST,optType);
    nodes[i] = FT;
  }

  double fu;
  double fd;
  for (int i=n-1; i>=0; i--) {
    for (int j=0; j<i+1; j++) {
      fu = nodes[j+1];
      fd = nodes[j];
      nodes[j] = discount * (p * fu + (1-p) * fd);
    }
  }

  return nodes[0];
}


int main() {

  // CALL EXAMPLES

  // Hull 13.1

  double T = 0.25; // Maturity
  double K = 21.0; // Strike price
  char optType = 'c';

  double S0 = 20.0; // Stock start price
  double r = 0.04; // Risk neutral return

  double u = 1.1; // Return if stock price goes up
  double d = 0.9; // Loss is stock price goes down
  int n = 1; // Time steps
  double f = binomialPrice(T,K,optType,S0,r,u,d,n);
  std::cout << "Hull 13.1. Option price should be 0.5450." << std::endl;
  std::cout << "f: "; LOG(f);

  // Hull 13.3

  T = 0.5;
  K = 21;
  optType = 'c';

  S0 = 20;
  r = 0.04;

  u = 1.1;
  d = 0.9;
  n = 2;
  f = binomialPrice(T,K,optType,S0,r,u,d,n);
  std::cout << "Hull 13.3. Option price should be 0.9497." << std::endl;
  std::cout << "f: "; LOG(f);

  // Additional example

  T = 1.0;
  K = 100.0;
  optType = 'c';

  S0 = 100.0;
  r = 0.05;

  u = 1.2;
  d = 0.9;
  n = 1;
  f = binomialPrice(T,K,optType,S0,r,u,d,n);
  std::cout << "Additional example. Option price should be 9.5929." << std::endl;
  std::cout << "f: "; LOG(f);

  // Additional example

  T = 1.0;
  K = 100.0;
  optType = 'c';

  S0 = 100.0;
  r = 0.05;

  double sigma = 0.2;
  u = std::exp(sigma * std::sqrt(0.01));
  d = 1 / u;
  n = 100;
  f = binomialPrice(T,K,optType,S0,r,u,d,n);
  std::cout << "Additional example. Option price should be approximately 10.43." << std::endl;
  std::cout << "f: "; LOG(f);

  // PUT EXAMPLES
  
  // Hull 13.4

  T = 2;
  K = 52;
  optType = 'p';

  S0 = 50;
  r = 0.05;

  u = 1.2;
  d = 0.8;
  n = 2;
  f = binomialPrice(T,K,optType,S0,r,u,d,n);
  std::cout << "Hull 13.4. Option price should be 4.1923." << std::endl;
  std::cout << "f: "; LOG(f);

  // ADDITIONAL

  T = 1;
  K = 100;
  optType = 'p';

  S0 = 100;
  r = 0.05;

  n = 100;
  sigma = 0.0;
  u = std::exp(sigma * std::sqrt(T/n));
  d = 1 / u;
  f = binomialPrice(T,K,optType,S0,r,u,d,n);
  std::cout << "Hull 13.4. Option price should be 4.1923." << std::endl;
  std::cout << "f: "; LOG(f);
}
