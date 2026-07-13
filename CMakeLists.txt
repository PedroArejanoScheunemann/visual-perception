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

option(VP_BUILD_ALL_TESTS         "Build all tests"         OFF)
option(VP_BUILD_UNIT_TESTS        "Build unit tests"        OFF)
option(VP_BUILD_INTEGRATION_TESTS "Build integration tests" OFF)

option(VP_BUILD_EXAMPLES          "Build examples"          OFF)

# ============================================================================
# Build Presets
# ============================================================================

if(VP_BUILD_ALL_TESTS)
    set(VP_BUILD_UNIT_TESTS        ON)
    set(VP_BUILD_INTEGRATION_TESTS ON)
endif()

# ============================================================================
# Testing
# ============================================================================

if(VP_BUILD_UNIT_TESTS OR
   VP_BUILD_INTEGRATION_TESTS)
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
