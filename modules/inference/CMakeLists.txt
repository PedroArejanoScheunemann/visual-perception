add_library(vp_inference)

target_sources(
    vp_inference
    PRIVATE
        src/inference.c
)

target_include_directories(
    vp_inference
    PUBLIC
        include
)

target_link_libraries(
    vp_inference
    PUBLIC
        vp_common
)

if(VP_BUILD_UNIT_TESTS)
    add_subdirectory(tests)
endif()
