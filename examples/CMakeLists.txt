cmake_minimum_required(VERSION 3.14)

add_executable(examples examples_main.cpp)
set_property(TARGET examples PROPERTY CXX_STANDARD 20)
target_link_libraries(examples core)
