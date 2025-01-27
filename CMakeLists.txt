cmake_minimum_required(VERSION 3.15)
project(NumericServerClient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS system)

if (NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found")
endif()

add_subdirectory(src/NumericServer)
add_subdirectory(src/NumericClient)
