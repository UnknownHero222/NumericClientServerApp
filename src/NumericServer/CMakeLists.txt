project(NumericServer)

file(GLOB_RECURSE SERVER_SOURCES src/*.cpp)

add_executable(NumericServer ${SERVER_SOURCES})


target_include_directories(NumericServer PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(NumericServer PRIVATE 
                                    common
                                    Boost::program_options
)
