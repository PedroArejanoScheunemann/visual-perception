add_subdirectory(pipeline)

add_library(vp_yolo11 yolo11_person_detector.cpp)

add_library(Vision::Inference::Yolo11 ALIAS vp_yolo11)

target_include_directories(vp_yolo11
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(vp_yolo11
    PUBLIC
        Vision::Inference::Models
        Vision::Inference::Person::Domain
        Vision::Inference::Pipeline
)
