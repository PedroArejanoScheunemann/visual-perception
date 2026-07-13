add_library(vp_yolo11_pipeline yolo11_preprocessor.cpp
                               yolo11_decoder.cpp)

add_library(Vision::Inference::Pipeline ALIAS vp_yolo11_pipeline)

target_include_directories(vp_yolo11_pipeline
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(vp_yolo11_pipeline
    PUBLIC
        Vision::Inference::Backend
        Vision::Inference::Person::Domain
)
