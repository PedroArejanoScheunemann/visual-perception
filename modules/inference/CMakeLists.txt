add_subdirectory(backend)
add_subdirectory(models)

add_library(vp_inference INTERFACE)

add_library(Vision::Inference ALIAS vp_inference)

target_include_directories(vp_inference
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(vp_inference
    INTERFACE
        Vision::Inference::Backend
        Vision::Inference::Models
        Vision::Inference::Engine
)

if(VP_BUILD_UNIT_TESTS)
    add_subdirectory(tests)
endif()
