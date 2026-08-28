#pragma once

#include "bounding_box.hpp"

namespace vp
{

/**
 * @brief Describes the geometric transformation applied to an image.
 *
 * Stores the information required to convert coordinates from the
 * model input space back to the original image space.
 */
class ImageTransform
{
public:

    /**
     * @brief Constructs an image transform.
     *
     * @param scale Scale applied to the original image.
     * @param padding_x Horizontal padding introduced by the transformation.
     * @param padding_y Vertical padding introduced by the transformation.
     */
    ImageTransform(float scale, float padding_x, float padding_y);

    /**
     * @brief Converts a bounding box from model coordinates to original
     * image coordinates.
     *
     * @param box Bounding box in model coordinates.
     *
     * @return Bounding box in original image coordinates.
     */
    BoundingBox ToOriginal(const BoundingBox& box) const;

private:

    float scale_;
    float padding_x_;
    float padding_y_;
};

} // namespace vp
