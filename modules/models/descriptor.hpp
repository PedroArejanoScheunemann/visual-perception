#pragma once

#include <array>
#include <cstdint>
#include <string_view>

namespace vp
{

/**
 * @brief Describes an inference model.
 *
 * This descriptor uniquely identifies the inference model implementation to be
 * created, including the detection category, inference backend and model.
 */
struct ModelDescriptor
{
    /**
     * @brief Supported detection categories.
     */
    enum class DetectionCategory : uint8_t
    {
        Object,
        Face,
        Surfboard,

        Count
    };

    /**
     * @brief Supported inference backends.
     */
    enum class BackendType : uint8_t
    {
        Onnx,
        CoreML,

        Count
    };

    /**
     * @brief Supported inference models.
     */
    enum class ModelType : uint8_t
    {
        Yolo11n,
        Yolo11s,
        Yolo11m,
        Yolo11l,
        Yolo11x,

        Count
    };

    /**
     * Detection category.
     */
    DetectionCategory category;

    /**
     * Inference backend.
     */
    BackendType backend;

    /**
     * Inference model.
     */
    ModelType model;

    /**
     * @brief Returns the directory name of a detection category.
     *
     * @param category Detection category.
     *
     * @return Directory name.
     */
    static constexpr std::string_view CategoryName(DetectionCategory category)
    {
        return kCategoryNames[static_cast<size_t>(category)];
    }

    /**
     * @brief Returns the file name of an inference model.
     *
     * @param model Inference model.
     *
     * @return Model name.
     */
    static constexpr std::string_view ModelName(ModelType model)
    {
        return kModelNames[static_cast<size_t>(model)];
    }

    /**
     * @brief Returns the file extension associated with an inference backend.
     *
     * @param backend Inference backend.
     *
     * @return File extension without the leading dot.
     */
    static constexpr std::string_view BackendExtension(BackendType backend)
    {
        return kBackendExtensions[static_cast<size_t>(backend)];
    }

private:

    inline static constexpr std::array<std::string_view,
        static_cast<size_t>(DetectionCategory::Count)>
        kCategoryNames{
            "object",
            "face",
            "surferboard"
        };

    inline static constexpr std::array<std::string_view,
        static_cast<size_t>(BackendType::Count)>
        kBackendExtensions{
            "onnx",
            "mlpackage"
        };

    inline static constexpr std::array<std::string_view,
        static_cast<size_t>(ModelType::Count)>
        kModelNames{
            "yolo11n",
            "yolo11s",
            "yolo11m",
            "yolo11l",
            "yolo11x"
        };
};

using DetectionCategory = ModelDescriptor::DetectionCategory;
using BackendType = ModelDescriptor::BackendType;
using ModelType = ModelDescriptor::ModelType;

} // namespace vp
