add_library(vp_preprocessing)

target_sources(
    vp_preprocessing
    PRIVATE
        src/preprocessing.c
)

target_include_directories(
    vp_preprocessing
    PUBLIC
        include
)

target_link_libraries(
    vp_preprocessing
    PUBLIC
        vp_common
)

if(VP_BUILD_UNIT_TESTS)
    add_subdirectory(tests)
endif()
