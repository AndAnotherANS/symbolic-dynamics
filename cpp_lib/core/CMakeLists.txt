cmake_minimum_required(VERSION 3.14)

# Create the library
add_library(core SHARED
        src/Utils.cpp
        src/SFT.cpp
        src/SoficShift.cpp
        src/ShiftSpace.cpp
        src/BlockCode.cpp
        src/CylinderSet.cpp
        src/Measure.cpp
)


# Link libraries
target_link_libraries(core)
target_link_libraries(core Eigen3::Eigen)

target_include_directories(core PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Install the library
install(TARGETS core
        EXPORT coreTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

# Install all header files
install(DIRECTORY include/
        DESTINATION include
        FILES_MATCHING PATTERN "*.hpp"
)

# Export targets for find_package
install(EXPORT coreTargets
        FILE coreTargets.cmake
        NAMESPACE core::
        DESTINATION lib/cmake/core
)

# Add tests
add_executable(test_graph test/test_graph.cpp)
target_link_libraries(test_graph gtest_main core)
add_test(NAME Graph COMMAND test_graph)

add_executable(test_sft test/test_sft.cpp)
target_link_libraries(test_sft gtest_main core)
add_test(NAME SFT COMMAND test_sft)

add_executable(test_strongly_connected_components test/test_strongly_connected_components.cpp)
target_link_libraries(test_strongly_connected_components gtest_main core)
add_test(NAME StronglyConnectedComponents COMMAND test_strongly_connected_components)

add_executable(test_period test/test_period.cpp)
target_link_libraries(test_period gtest_main core)
add_test(NAME Acyclic COMMAND test_period)

add_executable(test_cylinder test/test_cylinder_sets.cpp)
target_link_libraries(test_cylinder gtest_main core)
add_test(NAME CylinderSet COMMAND test_cylinder)