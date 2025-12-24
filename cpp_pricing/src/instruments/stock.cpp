#include "../../include/instruments/stock.h"

double Stock::spot() const {
  return spot_;
}

const Dividend& Stock::dividends() const {
  return *dividend_;
}

const std::string& Stock::name() const {
  return name_;
}
