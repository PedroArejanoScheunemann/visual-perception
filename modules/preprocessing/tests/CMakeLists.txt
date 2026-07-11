add_executable(vp_preprocessing_tests)

target_sources(
    vp_preprocessing_tests
    PRIVATE
        stub_test.cpp
)

target_link_libraries(
    vp_preprocessing_tests
    PRIVATE
        vp_preprocessing
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(vp_preprocessing_tests)
