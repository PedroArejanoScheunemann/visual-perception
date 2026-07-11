add_library(vp_common)

target_sources(
    vp_common
    PRIVATE
        src/common.c
)

target_include_directories(
    vp_common
    PUBLIC
        include
)

if(VP_BUILD_UNIT_TESTS)
    add_subdirectory(tests)
endif()
