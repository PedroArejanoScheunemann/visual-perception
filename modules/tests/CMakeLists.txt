add_executable(vp_integration_tests stub_test.cpp)

target_link_libraries(vp_integration_tests
    PRIVATE
        GTest::gtest_main
        Vision::Inference
)

include(GoogleTest)

gtest_discover_tests(vp_integration_tests)
