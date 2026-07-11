add_executable(vp_common_tests)

target_sources(
    vp_common_tests
    PRIVATE
        stub_test.cpp
)

target_link_libraries(
    vp_common_tests
    PRIVATE
        vp_common
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(vp_common_tests)
