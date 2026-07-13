add_executable(vp_inference_tests stub_test.cpp)

target_link_libraries(vp_inference_tests
    PRIVATE
        GTest::gtest_main
        Vision::Inference
)

include(GoogleTest)

gtest_discover_tests(vp_inference_tests)
