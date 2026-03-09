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
    double St;
    double currPayoff;
    double currIntrinsic;
    for (int i=n-1; i>=0; i--) {
      for (int j=0; j<i+1; j++) {
        fu = nodes[j+1];
        fd = nodes[j];
        St = S0 * std::pow(u,j) * std::pow(d,i-j);
        currPayoff = payoff(K,St,optType);
        currIntrinsic = discount * (p * fu + (1-p) * fd);
        nodes[j] = std::max(currPayoff,currIntrinsic);
      }
    }

    return nodes[0];
}


int main() {

  // PUT EXAMPLES

  // Hull 13.5

  double T = 2;
  double K = 52;
  char optType = 'p';

  double S0 = 50;
  double r = 0.05;

  double u = 1.2;
  double d = 0.8;
  int n = 2;
  double f = binomialPrice(T,K,optType,S0,r,u,d,n);
  std::cout << "Hull 13.5. Option price should be 5.0894." << std::endl;
  std::cout << "f: "; LOG(f);

}
