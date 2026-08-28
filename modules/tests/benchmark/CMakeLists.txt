add_subdirectory(reporter)

add_executable(vp_benchmarks yolo11_image_benchmark.cpp)

target_link_libraries(vp_benchmarks PRIVATE VP::Engine
                                            VP::PerceptionVisualizers
                                            VP::BenchmarkReporter
                                            GTest::gtest
                                            GTest::gtest_main)

target_compile_definitions(vp_benchmarks PRIVATE VP_IMAGES_DIR="${PROJECT_SOURCE_DIR}/assets/images"
                                                 VP_BENCHMARK_OUTPUT_DIR="${PROJECT_SOURCE_DIR}/benchmarks")

include(GoogleTest)

gtest_discover_tests(vp_benchmarks)
