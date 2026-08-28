#pragma once

#include "tensor.hpp"
#include "image_transform.hpp"
#include "frame.hpp"

namespace vp
{

/**
 * @brief Preprocesses an image for the YOLO11 model.
 */
class Yolo11Preprocessor
{
public:

    /**
     * @brief Constructs a YOLO11 preprocessor.
     *
     * @param input Input tensor.
     */
    explicit Yolo11Preprocessor(Tensor& input);

    /**
     * @brief Preprocesses an image.
     *
     * The image is resized using letterbox, converted from BGR to RGB,
     * normalized to the [0, 1] range and converted from HWC to CHW layout.
     *
     * @param frame Input image.
     */
    void Process(const Frame& frame);

    /**
     * @brief Returns the image transformation.
     *
     * The returned reference remains valid for the lifetime of the
     * preprocessor.
     *
     * @return Constant reference to the internal image transformation.
     */
    const ImageTransform& Transform() const;

private:

    void ValidateInput() const;

private:

    Tensor& input_;

    ImageTransform transform_{1.0F, 0.0F, 0.0F};
};

} // namespace vp
