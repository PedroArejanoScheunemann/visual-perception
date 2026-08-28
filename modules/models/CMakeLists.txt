add_library(vp_models STATIC)

add_library(VP::Models ALIAS vp_models)

target_compile_definitions(vp_models PRIVATE VP_ASSETS_DIR="${PROJECT_SOURCE_DIR}/assets")

target_sources(vp_models PRIVATE factory.cpp)

target_include_directories(vp_models PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(vp_models PUBLIC VP::Backend
                                       VP::Perception
                                       VP::Profiling
                                       VP::Types::OpenCV)

add_subdirectory(object)
