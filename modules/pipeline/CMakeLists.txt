add_library(vp_pipeline)

target_sources(
    vp_pipeline
    PRIVATE
        src/pipeline.c
)

target_include_directories(
    vp_pipeline
    PUBLIC
        include
)

target_link_libraries(
    vp_pipeline
    PUBLIC
        vp_common
        vp_preprocessing
        vp_inference
        vp_tracking
)

if(VP_BUILD_UNIT_TESTS)
    add_subdirectory(tests)
endif()
