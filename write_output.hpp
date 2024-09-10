#pragma once

#include "candles_factory.hpp"

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

namespace csv
{
inline void write_candles(const fs::path& filepath, const std::vector<candles::candle>& candles)
{
    fs::directory_entry dir(filepath);
    if (!dir.exists())
        throw std::runtime_error("Unvalid directory for output candles .csv file!");

    std::ofstream output(std::string(filepath) + "candles.csv", std::ios::out);
    if (!output.is_open())
        throw std::runtime_error("Can't create candles .csv file!");

    output << "Time" << ","
           << "Open" << ","
           << "High" << ","
           << "Low" << ","
           << "Close" << ","
           << "Volume" << "\n"; 

    for (const auto& candle : candles)
        output << candle.time << ","
           << candle.open << ","
           << candle.high << ","
           << candle.low << ","
           << candle.close << ","
           << candle.volume << "\n";   
}
}