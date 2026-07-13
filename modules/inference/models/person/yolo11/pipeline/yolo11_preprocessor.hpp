#pragma once

#include <cstddef>
#include "domain/tensor.hpp"
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
     * @param frame Input image.
     */
    void Process(const Frame& frame) const;

private:

    Tensor& input_;
    std::size_t width_;
    std::size_t height_;
};

} // namespace vp
