add_executable(vp_example)

target_sources(
    vp_example
    PRIVATE
        main.c
)

target_link_libraries(
    vp_example
    PRIVATE
        vp_modules
)
