add_executable(vp_system_tests)

target_sources(vp_system_tests PRIVATE object_detection_test.cpp)

target_compile_definitions(vp_system_tests PRIVATE VP_ASSETS_DIR="${PROJECT_SOURCE_DIR}/assets")

target_link_libraries(vp_system_tests PRIVATE VP::Engine
                                              GTest::gtest
                                              GTest::gtest_main)

include(GoogleTest)

gtest_discover_tests(vp_system_tests)
