project(NumericClient)

file(GLOB_RECURSE CLIENT_SOURCES src/*.cpp)

add_executable(NumericClient ${CLIENT_SOURCES})

target_include_directories(NumericClient PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(NumericClient PRIVATE ${Boost_LIBRARIES})
