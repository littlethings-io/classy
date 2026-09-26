# Called by each module's CMakeLists.txt. Source files and public headers are
# picked up automatically from that module's src/ and inc/ directories.
function(add_classy_module module_name)
    file(GLOB_RECURSE module_sources CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx"
    )

    if(module_sources)
        add_library(${module_name} STATIC ${module_sources})
        target_include_directories(${module_name}
            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc"
        )
        target_compile_features(${module_name} PUBLIC cxx_std_17)
    else()
        # Empty starter modules remain valid until their first source is added.
        add_library(${module_name} INTERFACE)
        target_include_directories(${module_name}
            INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/inc"
        )
    endif()

    set_property(GLOBAL APPEND PROPERTY CLASSY_MODULE_TARGETS ${module_name})

    if(BUILD_UNIT_TESTS)
        file(GLOB_RECURSE module_test_sources CONFIGURE_DEPENDS
            "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cc"
            "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cxx"
            "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cc"
            "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cxx"
        )

        if(module_test_sources)
            set(test_target "${module_name}_tests")
            add_executable(${test_target} ${module_test_sources})
            target_link_libraries(${test_target}
                PRIVATE ${module_name} GTest::gtest_main
            )
            target_compile_features(${test_target} PRIVATE cxx_std_17)
            gtest_discover_tests(${test_target})
            set_property(GLOBAL APPEND PROPERTY CLASSY_TEST_TARGETS ${test_target})
        endif()
    endif()
endfunction()

# Any direct child with a CMakeLists.txt is a module. CMake re-checks this glob
# when building, and run.py also configures before every build.
file(GLOB module_entries CONFIGURE_DEPENDS
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/*"
)

foreach(module_dir IN LISTS module_entries)
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${module_dir}"
       AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${module_dir}/CMakeLists.txt")
        add_subdirectory("${module_dir}")
    endif()
endforeach()

# modules_main is the application's entry module. Linking every other module to
# it exposes their inc/ folders there and ensures all module libraries build.
get_property(classy_modules GLOBAL PROPERTY CLASSY_MODULE_TARGETS)
list(REMOVE_ITEM classy_modules modules_main)
if(TARGET modules_main AND classy_modules)
    target_link_libraries(modules_main PUBLIC ${classy_modules})
endif()
