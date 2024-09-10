#pragma once

#include "candles_factory.hpp"

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

namespace csv
{
inline void write_candles(const fs::path& dirpath, const std::vector<candles::candle>& candles)
{
    fs::directory_entry dir(dirpath);
    if (!dir.exists())
        throw std::runtime_error("Unvalid directory for output candles .csv file!");

    std::ofstream output(std::string(dirpath) + "candles.csv", std::ios::out);
    if (!output.is_open())
        throw std::runtime_error("Can't create candles .csv file!");

    output << "Time" << ","
           << "Open" << ","
           << "High" << ","
           << "Low" << ","
           << "Close" << ","
           << "Volume" << std::endl;

    for (const auto& candle : candles)
        output << candle.time << ","
           << candle.open << ","
           << candle.high << ","
           << candle.low << ","
           << candle.close << ","
           << candle.volume << std::endl;
}

inline void write_sma_values(const fs::path& dirpath, const std::vector<double>& sma_values)
{
    fs::directory_entry dir(dirpath);
    if (!dir.exists())
        throw std::runtime_error("Unvalid directory for output sma values .csv file!");

    std::ofstream output(std::string(dirpath) + "sma_values.csv", std::ios::out);
    if (!output.is_open())
        throw std::runtime_error("Can't create sma values .csv file!");

    output << "SMA" << std::endl;
    for (double sma : sma_values)
        output << std::to_string(sma) << std::endl;
}
}
