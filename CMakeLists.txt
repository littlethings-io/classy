cmake_minimum_required(VERSION 3.20)

project(
    classy
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_UNIT_TESTS "Build the module GoogleTest tests" OFF)

if(BUILD_UNIT_TESTS)
    enable_testing()

    # GoogleTest is bundled so test builds never need a network connection.
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
    add_subdirectory(extern/googletest EXCLUDE_FROM_ALL)
    include(GoogleTest)
endif()

# Modules are added before the application so their targets are available to it.
add_subdirectory(modules)

if(BUILD_UNIT_TESTS)
    get_property(classy_test_targets GLOBAL PROPERTY CLASSY_TEST_TARGETS)
    add_custom_target(unit_tests DEPENDS ${classy_test_targets})
endif()

add_subdirectory(main)
