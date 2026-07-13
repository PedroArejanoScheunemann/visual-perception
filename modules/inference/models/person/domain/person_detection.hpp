#pragma once

#include "bounding_box.hpp"

namespace vp
{

/**
 * @brief Represents a detected person.
 */
class PersonDetection
{
public:

    /**
     * @brief Bounding box of the detected person.
     */
    BoundingBox bounding_box;

    /**
     * @brief Detection confidence.
     */
    float confidence = 0.0F;
};

} // namespace vp
