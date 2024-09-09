#pragma once

#include <ctime>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

namespace csv
{
struct quote
{
    time_t time;
    double price;
    double volume;
};

std::vector<quote> create_quotes_data(const fs::path& input_csv);
}