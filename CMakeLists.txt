cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)
project(quote-analizer)

find_package(cxxopts REQUIRED)

add_executable(quote-analizer 
    candles_factory.cpp
    candles_factory.hpp
    main.cpp 
    time_helpers.hpp
    quotes_reader.hpp 
    quotes_reader.cpp
    sma_factory.hpp
    sma_factory.cpp
    write_output.hpp
)

target_link_libraries(quote-analizer cxxopts::cxxopts)
install(TARGETS quote-analizer
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
