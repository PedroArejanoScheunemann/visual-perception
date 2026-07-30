include(FetchContent)

set(ONNXRUNTIME_VERSION "1.23.0")

FetchContent_Declare(
    ONNXRuntime
    URL "https://github.com/microsoft/onnxruntime/releases/download/v${ONNXRUNTIME_VERSION}/onnxruntime-linux-x64-${ONNXRUNTIME_VERSION}.tgz"
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_GetProperties(ONNXRuntime)

if(NOT ONNXRuntime_POPULATED)
    message(STATUS "Downloading ONNX Runtime ${ONNXRUNTIME_VERSION}")
    FetchContent_Populate(ONNXRuntime)
endif()

add_library(onnxruntime SHARED IMPORTED GLOBAL)

add_library(ThirdParty::ONNXRuntime ALIAS onnxruntime)

set_target_properties(onnxruntime PROPERTIES
    IMPORTED_LOCATION
        "${onnxruntime_SOURCE_DIR}/lib/libonnxruntime.so"

    INTERFACE_INCLUDE_DIRECTORIES
        "${onnxruntime_SOURCE_DIR}/include"
)
