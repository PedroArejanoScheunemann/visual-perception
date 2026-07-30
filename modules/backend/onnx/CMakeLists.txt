include(${PROJECT_SOURCE_DIR}/cmake/dependencies/ONNXRuntime.cmake)

target_sources(vp_backend PRIVATE onnx_backend.cpp)

target_include_directories(vp_backend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(vp_backend PUBLIC ThirdParty::ONNXRuntime)
