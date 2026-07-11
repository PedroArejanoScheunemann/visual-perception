add_executable(vp_inference_tests)

target_sources(
    vp_inference_tests
    PRIVATE
        stub_test.cpp
)

target_link_libraries(
    vp_inference_tests
    PRIVATE
        vp_inference
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(vp_inference_tests)
