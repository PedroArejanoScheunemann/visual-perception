add_library(vp_benchmark_reporter STATIC benchmark_reporter.cpp)

add_library(VP::BenchmarkReporter ALIAS vp_benchmark_reporter)

target_include_directories(vp_benchmark_reporter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(vp_benchmark_reporter PUBLIC VP::Profiling
                                                   VP::Types::OpenCV)

target_compile_features(vp_benchmark_reporter PUBLIC cxx_std_20)
