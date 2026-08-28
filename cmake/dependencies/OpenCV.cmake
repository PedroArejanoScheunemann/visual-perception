if(TARGET ThirdParty::OpenCV)
    return()
endif()

find_package(OpenCV CONFIG REQUIRED COMPONENTS core
                                               imgcodecs)

add_library(ThirdParty::OpenCV INTERFACE IMPORTED)

target_include_directories(ThirdParty::OpenCV INTERFACE ${OpenCV_INCLUDE_DIRS})

target_link_libraries(ThirdParty::OpenCV INTERFACE ${OpenCV_LIBS})
