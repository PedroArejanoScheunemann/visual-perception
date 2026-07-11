add_executable(vp_integration_tests)

target_sources(
    vp_integration_tests
    PRIVATE
        stub_test.cpp
)

target_link_libraries(
    vp_integration_tests
    PRIVATE
        vp_modules
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(vp_integration_tests)
