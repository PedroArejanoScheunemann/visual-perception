add_executable(vp_system_tests)

target_sources(
    vp_system_tests
    PRIVATE
        stub_test.cpp
)

target_link_libraries(
    vp_system_tests
    PRIVATE
        vp_modules
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(vp_system_tests)
