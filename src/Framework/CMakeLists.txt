# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0)

project(FrameworkLayer)
add_sources(. SRCS)

add_library(FrameworkLayer STATIC ${SRCS})

target_link_libraries(FrameworkLayer Domain Data)