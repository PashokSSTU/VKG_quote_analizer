#pragma once

#include "quotes_reader.hpp"

namespace candles
{
struct candle
{
    candle() : time(), open(0), high(0), low(0), close(0), volume(0)
    {
    }

    static inline bool is_empty(const candle current_candle)
    {
        return current_candle.time.empty() && !current_candle.open && 
               !current_candle.high && !current_candle.low && 
               !current_candle.close && !current_candle.volume;
    }

    std::string time;    // ISO 8601 formatted time
    double open;
    double high;
    double low;
    double close;
    double volume;
};
   
std::vector<candle> create_candles(const std::vector<csv::quote>& quotes, int candle_period);
}