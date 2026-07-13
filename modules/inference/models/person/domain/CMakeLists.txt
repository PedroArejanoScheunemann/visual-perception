add_library(vp_person_domain person_detections.cpp)

add_library(Vision::Inference::Person::Domain ALIAS vp_person_domain)

target_include_directories(vp_person_domain
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
