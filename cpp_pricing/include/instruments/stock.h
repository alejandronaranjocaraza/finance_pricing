#pragma once

#include <memory>
#include <iostream>
#include "instrument.h"

class Dividend;

class Stock : public Instrument {
public:
 Stock(
     double spot,
     std::shared_ptr<const Dividend> dividend,
     std::string name = ""
     ) :
   spot_{spot},
   dividend_{std::move(dividend)},
   name_{std::move(name)}
 {}

 double spot() const;
 const Dividend& dividends() const;
 const std::string& name() const;

private:
 double spot_;
 std::shared_ptr<const Dividend> dividend_;
 std::string name_;
};
