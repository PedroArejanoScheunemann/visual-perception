add_library(vp_perception STATIC)

add_library(VP::Perception ALIAS vp_perception)

target_sources(vp_perception PRIVATE object_detections.cpp
                                     perception_state.cpp)

target_include_directories(vp_perception PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(vp_perception PUBLIC VP::Types)

add_subdirectory(visualizers)
