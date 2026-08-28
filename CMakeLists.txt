# ============================================================================
# Project
# ============================================================================

cmake_minimum_required(VERSION 3.20)

project(
    visual_perception
    VERSION 0.1.0
    DESCRIPTION "Real-time visual perception library"
    LANGUAGES C CXX
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
option(VP_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

# ============================================================================
# C/C++ Standard
# ============================================================================

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ============================================================================
# Build Options
# ============================================================================

option(VP_BUILD_COMPONENT_TESTS "Build component tests"       OFF)
option(VP_BUILD_SYSTEM_TESTS    "Build system tests"          OFF)

option(VP_BUILD_EXAMPLES        "Build examples"              OFF)

option(VP_ENABLE_ONNX           "Enable ONNX Runtime backend" OFF)

option(VP_ENABLE_OPENCV         "Enable OpenCV support"       OFF)

# ============================================================================
# Testing
# ============================================================================

if(VP_BUILD_COMPONENT_TESTS OR VP_BUILD_SYSTEM_TESTS)
    enable_testing()
    include(cmake/dependencies/GoogleTest.cmake)
endif()

# ============================================================================
# Modules
# ============================================================================

add_subdirectory(modules)

# ============================================================================
# Examples
# ============================================================================

if(VP_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
