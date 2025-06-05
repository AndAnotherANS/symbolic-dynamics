cmake_minimum_required(VERSION 3.14)
project(SymbolicDynamics)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        e9092b12dc3cf617d47578f13a1f64285cfa5b2f
        FIND_PACKAGE_ARGS NAMES GTest
)
FetchContent_Declare(
        eigen3
        GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
        GIT_TAG        67eeba6e720c5745abc77ae6c92ce0a44aa7b7ae
        FIND_PACKAGE_ARGS NAMES Eigen3
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest eigen3)

option(native "Use native implementation of matrices" OFF)
option(BUILD_EXAMPLES "build examples" OFF)

if(NOT ${native})
    find_package(Eigen3 3.3 REQUIRED NO_MODULE)
    add_compile_definitions(MATRIX_EIGEN)
endif ()

message(STATUS "Examples: ${BUILD_EXAMPLES}")
if(${BUILD_EXAMPLES})
    add_subdirectory(examples)
endif()

enable_testing()
add_subdirectory(cpp_lib/core)


set_property(TARGET core PROPERTY CXX_STANDARD 20)

include(CMakePackageConfigHelpers)

install(EXPORT coreTargets
        FILE coreTargets.cmake
        NAMESPACE core::
        DESTINATION lib/cmake/core
)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/coreConfigVersion.cmake"
        VERSION 1.0
        COMPATIBILITY AnyNewerVersion
)

install(FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/coreConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/coreConfigVersion.cmake"
        DESTINATION lib/cmake/core
)
