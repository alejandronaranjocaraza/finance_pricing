#include <memory>

#include "../include/instruments/stock.h"

std::shared_ptr<Stock> makeStock(
    double spot,
    double yieldRate
    ) {

  auto dividend = std::make_shared<ContinuousDividend>(yieldRate);
  auto stock = std::make_shared<Stock>(spot, dividend);
  return stock;
}
