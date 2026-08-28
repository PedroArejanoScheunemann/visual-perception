add_executable(vp_system_tests)

target_sources(vp_system_tests PRIVATE object_detection_tests.cpp)

target_compile_definitions(vp_system_tests PRIVATE VP_IMAGES_DIR="${PROJECT_SOURCE_DIR}/assets/images"
                                                   VP_SYSTEM_TEST_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(vp_system_tests PRIVATE VP::Engine
                                              VP::Types::OpenCV
                                              GTest::gtest
                                              GTest::gtest_main)

include(GoogleTest)

gtest_discover_tests(vp_system_tests)
