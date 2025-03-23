cmake_minimum_required(VERSION 3.14)

# Create the library
add_library(core SHARED
    src/Graph.cpp
    src/Language.cpp
    src/SFT.cpp
    src/SoficShift.cpp
    src/ShiftSpace.cpp
)

# Include directories

target_include_directories(core PUBLIC include)

# Link libraries
target_link_libraries(core)

# Add tests
enable_testing()
add_executable(test_language test/test_language.cpp)
add_executable(test_graph test/test_graph.cpp)
target_link_libraries(test_language gtest_main core)
target_link_libraries(test_graph gtest_main core)
add_test(NAME Language COMMAND test_language)
add_test(NAME Graph COMMAND test_graph)