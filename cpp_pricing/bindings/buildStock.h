#pragma once

#include <memory>

class Stock;

std::shared_ptr<Stock> makeStock(
    double spot,
    double yieldRate
    );
