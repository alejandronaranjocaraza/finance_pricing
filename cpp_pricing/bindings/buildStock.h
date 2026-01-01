#pragma once

#include <memory>
#include <vector>
#include <array>

class Stock;

using CashFlows = std::vector<std::array<double, 2>>;

std::shared_ptr<Stock> makeStock(
    double spot,
    double yieldRate,
    const CashFlows* divCashFlow = nullptr
    );
