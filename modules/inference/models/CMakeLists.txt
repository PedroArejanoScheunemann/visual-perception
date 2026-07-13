add_subdirectory(person)

add_library(vp_inference_models INTERFACE)

add_library(Vision::Inference::Models ALIAS vp_inference_models)

target_include_directories(vp_inference_models
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(vp_inference_models
    INTERFACE
        Vision::Inference::Backend
        Vision::Inference::Person
)
