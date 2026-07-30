target_sources(vp_models PRIVATE yolo11_object_detector.cpp)

target_include_directories(vp_models PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(pipeline)
