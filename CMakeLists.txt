cmake_minimum_required(VERSION 3.14)
project(SymbolicDynamics)



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
