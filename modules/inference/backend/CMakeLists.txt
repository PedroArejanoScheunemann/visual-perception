add_library(vp_inference_backend
    domain/tensor.cpp
    domain/tensor_shape.cpp
    domain/tensor_specification.cpp
)

add_library(Vision::Inference::Backend ALIAS vp_inference_backend)

target_include_directories(vp_inference_backend
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# TO DO: link with backend dependencies
#target_link_libraries(vp_inference_backend
#    PUBLIC
#
#)
