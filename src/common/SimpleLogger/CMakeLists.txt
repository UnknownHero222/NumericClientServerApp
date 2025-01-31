cmake_minimum_required(VERSION 3.10)
project(SimpleLogger)

add_library(simple_logger STATIC simple_logger.cpp)

target_include_directories(simple_logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
