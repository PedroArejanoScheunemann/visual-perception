#include "image_transform.hpp"

#include <algorithm>
#include <stdexcept>

namespace vp
{

ImageTransform::ImageTransform(float scale, float padding_x, float padding_y) :
                               scale_(scale),
                               padding_x_(padding_x),
                               padding_y_(padding_y)
{
    if (scale_ <= 0.0F)
    {
        throw std::invalid_argument("Image transform scale must be greater than zero.");
    }
}

void ImageTransform::Update(float scale, float padding_x, float padding_y)
{
    scale_ = scale;
    padding_x_ = padding_x;
    padding_y_ = padding_y;
}

BoundingBox ImageTransform::ToOriginal(const BoundingBox& box) const
{
    BoundingBox result;

    result.x = (box.x - padding_x_) / scale_;
    result.y = (box.y - padding_y_) / scale_;
    result.width = box.width / scale_;
    result.height = box.height / scale_;

    return result;
}

} // namespace vp
