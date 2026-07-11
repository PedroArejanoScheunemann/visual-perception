add_executable(vp_tracking_tests)

target_sources(
    vp_tracking_tests
    PRIVATE
        stub_test.cpp
)

target_link_libraries(
    vp_tracking_tests
    PRIVATE
        vp_tracking
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(vp_tracking_tests)
