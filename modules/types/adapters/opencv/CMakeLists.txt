find_package(OpenCV CONFIG REQUIRED COMPONENTS core)

add_library(vp_types_adapter_opencv STATIC)

add_library(VP::Types::OpenCV ALIAS vp_types_adapter_opencv)

target_sources(vp_types_adapter_opencv PRIVATE frame_adapter.cpp)

target_include_directories(vp_types_adapter_opencv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                                           ${OpenCV_INCLUDE_DIRS})

target_link_libraries(vp_types_adapter_opencv PUBLIC VP::Types
                                                     ${OpenCV_LIBS})
