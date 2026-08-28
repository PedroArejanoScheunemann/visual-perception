option(VP_ENABLE_PROFILING "Enable runtime profiling instrumentation" OFF)

add_library(vp_profiling INTERFACE)

add_library(VP::Profiling ALIAS vp_profiling)

target_include_directories(vp_profiling INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

if(VP_ENABLE_PROFILING)
    add_library(vp_profiler STATIC internal/profiler.cpp)

    target_include_directories(vp_profiler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/internal)

    target_compile_features(vp_profiler PUBLIC cxx_std_20)

    target_link_libraries(vp_profiling INTERFACE vp_profiler)

    target_compile_definitions(vp_profiling INTERFACE VP_ENABLE_PROFILING)
endif()
