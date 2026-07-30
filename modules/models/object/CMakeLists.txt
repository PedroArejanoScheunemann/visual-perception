target_sources(vp_models PRIVATE object_detection_model.cpp)

target_include_directories(vp_models PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(yolo11)
