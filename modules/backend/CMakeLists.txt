add_library(vp_backend STATIC)

add_library(VP::Backend ALIAS vp_backend)

target_include_directories(vp_backend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(vp_backend PUBLIC VP::Types)

if(VP_ENABLE_ONNX)
    add_subdirectory(onnx)
endif()
