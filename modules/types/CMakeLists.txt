add_library(vp_types STATIC)

add_library(VP::Types ALIAS vp_types)

target_sources(vp_types PRIVATE tensor.cpp
                                tensor_shape.cpp
                                tensor_specification.cpp
                                image_transform.cpp)

target_include_directories(vp_types PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(adapters)
