# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0)

project(Data)
add_sources(. SRCS)

add_library(Data STATIC ${SRCS})

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(Data Domain nlohmann_json)