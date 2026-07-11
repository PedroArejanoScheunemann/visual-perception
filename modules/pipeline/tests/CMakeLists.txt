add_executable(vp_pipeline_tests)

target_sources(
    vp_pipeline_tests
    PRIVATE
        stub_test.cpp
)

target_link_libraries(
    vp_pipeline_tests
    PRIVATE
        vp_pipeline
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(vp_pipeline_tests)
