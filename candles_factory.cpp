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
    auto quote_start_tp = helpers::time_t_to_time_point(quotes.front().time);
    for (const auto& quote : quotes) 
    {
        auto quote_tp = helpers::time_t_to_time_point(quote.time);     
        auto period_start = helpers::round_to_period(quote_tp, quote_start_tp, candle_period);

        if (candles_keys.empty() ||
            candles_keys.back().time_since_epoch().count() != period_start.time_since_epoch().count())
            candles_keys.push_back(period_start);
        auto& candle = candles[period_start];

        if (candles::candle::is_empty(candle))
        {
            time_t time_t_start = std::chrono::system_clock::to_time_t(quote_tp);
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

    for (const auto& tp_key : candles_keys) 
    {
        auto& current_candle = candles.at(tp_key);
        if (candles::candle::is_empty(current_candle)) 
        {
            // Пропуск, заполняем значениями из предыдущей свечи
            current_candle = last_candle;
            std::stringstream ss;
            time_t time_t_start = std::chrono::system_clock::to_time_t(tp_key);
            ss << std::put_time(std::gmtime(&time_t_start), "%Y-%m-%dT%H:%M:%S");
            current_candle.time = ss.str();
        }

        last_candle = current_candle;
        result.push_back(current_candle);
    }

    return result;
}
}
