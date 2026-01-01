#include <stdexcept>
#include <memory>
#include <vector>
#include <array>
#include "buildStock.h"
#include "../include/instruments/stock.h"
#include "../include/instruments/dividend.h"

std::shared_ptr<Stock> makeStock(
    double stockSpot,
    double divYieldRate,
    const CashFlows* divCashFlow
    ) {
  if(divYieldRate!=0.0 && divCashFlow)
    throw std::invalid_argument("Stock must have discrete OR continuous dividend (but not both)");
  
  std::shared_ptr<Dividend> dividend;

  if(divCashFlow) {
    std::vector<Dividend::CashFlow> cashSchedule;
    cashSchedule.reserve(divCashFlow->size());
      for(const auto& div : *divCashFlow) {
        cashSchedule.push_back(Dividend::CashFlow{div[0],div[1]});
      }
    dividend = std::make_shared<DiscreteDividend>(std::move(cashSchedule));
  }
  else {
    dividend = std::make_shared<ContinuousDividend>(divYieldRate);
  }
  auto stock = std::make_shared<Stock>(stockSpot, std::move(dividend));
  return stock;
}
