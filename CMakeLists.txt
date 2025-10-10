cmake_minimum_required(VERSION 3.27.7)
include(cmake/macros.cmake) # include macros in a separate cmake file macros.cmake

LOGTHIS("Starting the main CMakeLists")

### including gcc options
include(cmake/gcc_options.cmake)

# project setup.
set(project_name classy)
set(project_version 0.0.0)
set(main_folder ${CMAKE_CURRENT_LIST_DIR}/main/src/main.cpp)

project(
    ${project_name}
    VERSION ${project_version}
    LANGUAGES CXX C ASM
)

### languages ###
enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

### subdirectories ###
add_subdirectory(main)

### linking ###

add_executable(${project_name} ${main_folder})

# make an ASM file also to see the ASM instructions.
add_custom_command(TARGET ${project_name} POST_BUILD
    COMMAND ${CMAKE_OBJDUMP}
    -C -S
    $<TARGET_FILE:${project_name}>
    > ${project_name}.asm
)

target_link_libraries(
    ${project_name}
    main
)
