add_subdirectory(domain)
add_subdirectory(yolo11)

add_library(vp_person INTERFACE)

add_library(Vision::Inference::Person ALIAS vp_person)

target_include_directories(vp_person
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(vp_person
    INTERFACE
        Vision::Inference::Person::Domain
        Vision::Inference::Yolo11
)
