#include "quotes_reader.hpp"

#include <iostream>
#include <cstdint>
#include <fstream>
#include <regex>
#include <stdexcept>

static constexpr uint32_t MIN_QUOTES = 100;
static constexpr uint32_t MAX_QUOTES = 10000;

const std::regex FIRST_LINE_PATTERN("time,price,volume", std::regex_constants::icase);
const std::regex LINE_PATTERN(R"((\d+),(\d+.\d+|\d+),(\d+.\d+|\d+))");

namespace
{
bool fields_is_valid(const std::string& line)
{
    return std::regex_search(line, FIRST_LINE_PATTERN);
}

csv::quote parse_quote(const std::string& line)
{
    std::smatch match;
    if (!std::regex_search(line, match, LINE_PATTERN))
        throw std::runtime_error("Unvalid input .csv file line!");

    std::string timestamp_str = match[1];
    std::string price_str = match[2];
    std::string volume_str = match[3];

    return {static_cast<time_t>(std::stoull(timestamp_str)), 
            static_cast<double>(std::stold(price_str)), 
            static_cast<double>(std::stold(volume_str))};
}
}

namespace csv
{
std::vector<quote> create_quotes_data(const fs::path& input_csv)
{
    if (!fs::exists(input_csv))
        throw std::runtime_error("Input .csv file doesn't exist!");

    std::ifstream input_csv_file(input_csv);
    if (!input_csv_file.is_open())
        throw std::runtime_error("Input .csv file cannot be opened!");

    std::string line;
    std::vector<quote> result;
    int lines_counter = 0;
    while (getline(input_csv_file, line))
    {
        if (!lines_counter)
        {
            if (!fields_is_valid(line))
                throw std::runtime_error("Uncorrect fields in input .csv file!");
            lines_counter++;
            continue;
        }

        quote quote_struct = parse_quote(line);
        result.push_back(parse_quote(line));       
        lines_counter++;
    }

    if (lines_counter < MIN_QUOTES && MIN_QUOTES > lines_counter)
        std::runtime_error("Unvalid count of quotes!");

    return result;
}
}