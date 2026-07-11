add_subdirectory(common)
add_subdirectory(preprocessing)
add_subdirectory(inference)
add_subdirectory(tracking)
add_subdirectory(pipeline)

add_library(vp_modules INTERFACE)

target_link_libraries(
    vp_modules
    INTERFACE
        vp_pipeline
)

if(VP_BUILD_INTEGRATION_TESTS)
    add_subdirectory(tests)
endif()
