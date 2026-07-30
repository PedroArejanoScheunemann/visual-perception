add_library(vp_engine engine.cpp)

add_library(VP::Engine ALIAS vp_engine)

target_include_directories(vp_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(vp_engine PUBLIC VP::Models
                                       VP::Perception)
