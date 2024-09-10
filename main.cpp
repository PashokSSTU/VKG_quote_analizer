#include "quotes_reader.hpp"
#include "candles_factory.hpp"
#include "write_output.hpp"
#include "sma_factory.hpp"

#include <iostream>
#include <cxxopts.hpp>

int main(int argc, char* argv[])
{
    try
    {
        cxxopts::Options options("quote-analizer", "CLI for analyzing quotes");
        options.add_options()
            ("f, file", "Input quotes .csv file", cxxopts::value<std::string>())
            ("o, output", "Output directory for .csv files (default: .)", cxxopts::value<std::string>())
            ("l, length", "Candlestick chart length", cxxopts::value<uint32_t>())
            ("p, period", "Moving average period", cxxopts::value<uint32_t>())
            ("h, help", "Usage help")
            ;

        auto result = options.parse(argc, argv);

        if (result.count("help"))
        {
            std::cout << options.help() << std::endl;
            return 0;
        }  

        std::string filepath = result["file"].as<std::string>();
        uint32_t candle_length = result["length"].as<uint32_t>();
        uint32_t sma_period = result["period"].as<uint32_t>();
        std::string output_dir = result["output"].as<std::string>();

        std::vector<csv::quote> quotes = csv::create_quotes_data(filepath);

        auto candles = candles::create_candles(quotes, candle_length);
        csv::write_candles(output_dir, candles);

        auto sma_values = sma::calc_sma_values(candles, sma_period);
        csv::write_sma_values(output_dir, sma_values);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
        

    return 0;
}
