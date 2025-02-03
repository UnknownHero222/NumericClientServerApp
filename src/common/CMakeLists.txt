cmake_minimum_required(VERSION 3.10)
project(CommonLib)

find_package(Boost REQUIRED COMPONENTS program_options)

add_library(common STATIC 
    SimpleLogger/simple_logger.cpp
    ConfigParser/config_parser.cpp
)

target_link_libraries(common PUBLIC Boost::program_options)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
