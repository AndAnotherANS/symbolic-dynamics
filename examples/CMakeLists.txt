cmake_minimum_required(VERSION 3.14)
project(Examples)

find_package(core REQUIRED PATHS ../install_dir)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
add_compile_definitions(MATRIX_EIGEN)

add_executable(examples examples_main.cpp)
target_link_libraries(examples core::core)
