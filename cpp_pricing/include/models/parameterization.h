#include <cmath>

struct Manual {
  static double p(double a, double u, double d) {
    return (a - d) / (u - d);
  }
};

struct CRR {
  static double u(double sigma, double dt) {
    return std::exp(sigma*std::sqrt(dt));
  }
  static double d(double sigma, double dt) {
    return std::exp(-sigma*std::sqrt(dt));
  }
  static double p(double a, double u, double d) {
    return (a - d) / (u - d);
  }
};
