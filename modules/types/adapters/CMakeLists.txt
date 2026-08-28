if(VP_ENABLE_OPENCV)
    include(${PROJECT_SOURCE_DIR}/cmake/dependencies/OpenCV.cmake)

    add_subdirectory(opencv)
endif()
