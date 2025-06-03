cmake_minimum_required(VERSION 3.14)
project(SymbolicDynamics)

cmake_policy(SET CMP0135 NEW)


include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

option(native "Use native implementation of matrices" OFF)

if(NOT ${native})
    find_package(Eigen3 3.3 REQUIRED NO_MODULE)
    add_compile_definitions(MATRIX_EIGEN)
endif ()

enable_testing()
add_subdirectory(cpp_lib/core)
set_property(TARGET core PROPERTY CXX_STANDARD 20)

add_executable(main main.cpp)
target_link_libraries(main core) # Link the core library to the main executable

add_subdirectory(examples)
