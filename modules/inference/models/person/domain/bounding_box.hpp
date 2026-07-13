#pragma once

namespace vp {

/**
 * @brief Axis-aligned bounding box.
 *
 * Coordinates are expressed in pixels.
 */
struct BoundingBox
{
    float x{0.0F};

    float y{0.0F};

    float width{0.0F};

    float height{0.0F};
};

} // namespace vp
