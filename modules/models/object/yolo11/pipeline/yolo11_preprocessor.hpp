#pragma once

#include <cstddef>
#include "tensor.hpp"
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
     * @param inputs Input tensors.
     */
    explicit Yolo11Preprocessor(std::vector<Tensor>& inputs);

    /**
     * @brief Preprocesses an image.
     *
     * @param frame Input image.
     */
    void Process(const Frame& frame) const;

private:

    std::vector<Tensor>& inputs_;
};

} // namespace vp
