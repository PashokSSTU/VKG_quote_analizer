#include "sma_factory.hpp"

static constexpr uint32_t MIN_SMA_PERIOD = 10;
static constexpr uint32_t MAX_SMA_PERIOD = 500;

namespace sma
{
std::vector<double> calc_sma_values(const std::vector<candles::candle>& candles, uint32_t sma_period)
{
    if (sma_period < MIN_SMA_PERIOD || sma_period > MAX_SMA_PERIOD)
        throw std::runtime_error("Unvalid SMA period!");

    if (candles.size() < sma_period)
        return std::vector<double>();

    std::vector<double> sma_values;

    double sum = 0.0;
    for (size_t i = 0; i < sma_period; ++i) {
        sum += candles[i].close;
    }

    sma_values.push_back(sum / sma_period);

    for (size_t i = sma_period; i < candles.size(); ++i) {
        sum = sum - candles[i - sma_period].close + candles[i].close;
        sma_values.push_back(sum / sma_period);
    }

    return sma_values;
}
}
