add_executable(vp_component_tests)

target_sources(vp_component_tests PRIVATE engine_tests.cpp
                                          factory_tests.cpp
                                          onnx_backend_tests.cpp)

target_compile_definitions(vp_component_tests PRIVATE VP_ASSETS_DIR="${PROJECT_SOURCE_DIR}/assets")

target_link_libraries(vp_component_tests PRIVATE VP::Engine
                                                 GTest::gtest
                                                 GTest::gtest_main)

include(GoogleTest)

gtest_discover_tests(vp_component_tests)
