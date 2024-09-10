#include "candles_factory.hpp"
#include "time_helpers.hpp"

#include <map>
#include <stdexcept>

static constexpr uint32_t MIN_PERIOD = 5;
static constexpr uint32_t MAX_PERIOD = 60;

namespace candles
{
std::vector<candle> create_candles(const std::vector<csv::quote>& quotes, int candle_period)
{
    if (candle_period < MIN_PERIOD || candle_period > MAX_PERIOD)
        throw std::runtime_error("Invalid candle period!");

    std::map<std::chrono::system_clock::time_point, candle> candles;
    std::vector<std::chrono::system_clock::time_point> candles_keys;

    for (const auto& quote : quotes) 
    {
        auto quote_tp = helpers::time_t_to_time_point(quote.time);
        candles_keys.push_back(quote_tp);

        auto period_start = helpers::round_to_period(quote_tp, candle_period);
        auto& candle = candles[period_start];

        if (candle.time.empty()) 
        {
            time_t time_t_start = std::chrono::system_clock::to_time_t(period_start);
            std::stringstream ss;
            ss << std::put_time(std::gmtime(&time_t_start), "%Y-%m-%dT%H:%M:%S");
            candle.time = ss.str();
            candle.open = quote.price;
            candle.high = quote.price;
            candle.low = quote.price;
            candle.close = quote.price;
            candle.volume = quote.volume;
        } 
        else 
        {
            candle.close = quote.price;
            candle.high = std::max(candle.high, quote.price);
            candle.low = std::min(candle.low, quote.price);
            candle.volume += quote.volume;
        }
    }

    std::vector<candle> result;
    candle last_candle;

    for (auto it = candles_keys.begin(); it != candles_keys.end(); ++it) 
    {
        auto& current_candle = candles.at(*it);
        if (candles::candle::is_empty(current_candle)) 
        {
            // Пропуск, заполняем значениями из предыдущей свечи
            current_candle = last_candle;
            std::stringstream ss;
            time_t time_t_start = std::chrono::system_clock::to_time_t(*it);
            ss << std::put_time(std::gmtime(&time_t_start), "%Y-%m-%dT%H:%M:%S");
            current_candle.time = ss.str();
        }

        last_candle = current_candle;
        result.push_back(current_candle);
    }

    return result;
}
}