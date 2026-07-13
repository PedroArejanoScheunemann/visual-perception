add_library(vp_inference_engine engine.cpp)

add_library(Vision::Inference::Engine ALIAS vp_inference_engine)

target_include_directories(vp_inference_engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(vp_inference_engine
    PUBLIC
        Vision::Inference::Models
        Vision::Inference::Yolo11
)
