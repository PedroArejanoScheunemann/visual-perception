if(VP_BUILD_COMPONENT_TESTS)
    add_subdirectory(component)
endif()

if(VP_BUILD_SYSTEM_TESTS)
    add_subdirectory(system)
endif()

if(VP_BUILD_BENCHMARKS)
    add_subdirectory(benchmark)
endif()
