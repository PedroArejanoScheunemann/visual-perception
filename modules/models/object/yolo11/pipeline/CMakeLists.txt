target_sources(vp_models PRIVATE yolo11_preprocessor.cpp
                                 yolo11_decoder.cpp)

target_include_directories(vp_models PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
