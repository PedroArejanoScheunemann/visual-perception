#pragma once

#include "bounding_box.hpp"

namespace vp
{

/**
 * @brief Represents a detected object.
 */
class ObjectDetection
{
public:

    /**
     * @brief Bounding box of the detected object.
     */
    BoundingBox bounding_box;

    /**
     * @brief Detection confidence.
     */
    float confidence = 0.0F;
};

} // namespace vp
