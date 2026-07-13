add_subdirectory(inference)
add_subdirectory(engine)

if(VP_BUILD_INTEGRATION_TESTS)
    add_subdirectory(tests)
endif()
