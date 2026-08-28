add_library(vp_perception_visualizers STATIC object_detection_visualizer.cpp)

add_library(VP::PerceptionVisualizers ALIAS vp_perception_visualizers)

target_include_directories(vp_perception_visualizers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(vp_perception_visualizers PUBLIC  VP::Perception
                                                        VP::Types::OpenCV)

target_compile_features(vp_perception_visualizers PUBLIC cxx_std_20)
