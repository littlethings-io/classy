cmake_minimum_required(VERSION 3.20)

project(
    classy
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Modules are added before the application so their targets are available to it.
add_subdirectory(modules)
add_subdirectory(main)
