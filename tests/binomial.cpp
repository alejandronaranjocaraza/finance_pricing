#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

double getPrice(
    double u,
    double d,
    double r,
    double S0,
    double K,
    double T,
    double n = 100,
    int type = 1
    ) {
  double dt = T/n;
  double discountFactor = std::exp(-r * dt);
  double growthFactor = std::exp( r * dt);
  double p = (growthFactor - d) / (u - d);
  std::vector<double> nodes(n+1);
  
  // Terminal Values
  if(type == 1) {
    for(int i=0; i <= n; i++) {
      double ST = S0 * (std::pow(u,i)) * (std::pow(d, n - i));
      nodes[i] = std::max(K-ST,0.0);
    }
  }
  if(type == 0) {
    for(int i=0; i <= n; i++) {
      double ST = S0 * (std::pow(u,i)) * (std::pow(d, n - i));
      nodes[i] = std::max(ST-K,0.0);
    }
  }

  // Backwards Induction
  for(int i = n-1; i >= 0; i--) {
    for(int j=0; j<=i; j++) {
      nodes[j] = discountFactor * (p * nodes[j+1] + (1-p) * nodes[j]);
    }
  }

  return nodes[0];
}

int main() {
  double p = getPrice(1.2, 0.8, 0.05, 50, 52, 2, 2);
  std::cout << p;
}
