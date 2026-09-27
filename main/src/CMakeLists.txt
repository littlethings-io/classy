add_executable(classy main.cpp)

if(NOT TARGET modules_main)
    message(FATAL_ERROR "The required modules_main module was not found")
endif()

target_link_libraries(classy PRIVATE modules_main)

# Keep the executable at the root of the selected CMake build tree.
set_target_properties(classy PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
