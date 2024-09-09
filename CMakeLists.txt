cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)
project(quote-analizer)

find_package(cxxopts REQUIRED)

add_executable(quote-analizer main.cpp quotes_reader.hpp quotes_reader.cpp)

target_link_libraries(quote-analizer cxxopts::cxxopts)