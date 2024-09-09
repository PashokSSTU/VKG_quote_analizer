#include "quotes_reader.hpp"

#include <iostream>
#include <cxxopts.hpp>

int main(int argc, char* argv[])
{
    try
    {
        cxxopts::Options options("quote-analizer", "CLI for analyzing quotes");
        options.add_options()
            ("f, file", "Input quotes .csv file", cxxopts::value<std::string>())
            ("o, output", "Output directory for .csv files (default: .)")
            ("l, length", "Candlestick chart length", cxxopts::value<uint32_t>())
            ("p, period", "Moving average period", cxxopts::value<double>())
            ("h, help", "Usage help")
            ;

        auto result = options.parse(argc, argv);

        if (result.count("help"))
        {
            std::cout << options.help() << std::endl;
            return 0;
        }  

        std::string filepath = result["file"].as<std::string>();
        std::vector<csv::quote> quotes = csv::create_quotes_data(filepath);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
        

    return 0;
}