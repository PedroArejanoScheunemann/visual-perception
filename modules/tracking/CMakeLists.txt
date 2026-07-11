add_library(vp_tracking)

target_sources(
    vp_tracking
    PRIVATE
        src/tracking.c
)

target_include_directories(
    vp_tracking
    PUBLIC
        include
)

target_link_libraries(
    vp_tracking
    PUBLIC
        vp_common
)

if(VP_BUILD_UNIT_TESTS)
    add_subdirectory(tests)
endif()
