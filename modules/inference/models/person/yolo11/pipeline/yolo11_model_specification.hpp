#pragma once

#include "domain/tensor_specification.hpp"

namespace vp
{

/**
 * @brief Describes the input and output tensor specifications of a YOLO11 model.
 */
struct Yolo11ModelSpecification
{
    /**
     * @brief Input tensor specification.
     */
    TensorSpecification input;

    /**
     * @brief Output tensor specification.
     */
    TensorSpecification output;
};

} // namespace vp

namespace vp::yolo11
{

/**
 * @brief YOLO11 person detector model specification.
 */
inline const Yolo11ModelSpecification kPersonDetector
{
    .input =
    {
        {1, 3, 640, 640},
        TensorType::Float32
    },

    .output =
    {
        {1, 84, 8400},
        TensorType::Float32
    }
};

} // namespace vp::yolo11
