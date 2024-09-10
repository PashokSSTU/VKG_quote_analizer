#pragma once

#include "candles_factory.hpp"

namespace sma
{
std::vector<double> calc_sma_values(const std::vector<candles::candle>& candles, uint32_t sma_period);
}
