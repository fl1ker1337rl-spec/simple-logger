cmake_minimum_required(VERSION 3.14)
project(logger LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(logger STATIC
    src/Logger.cpp
)

