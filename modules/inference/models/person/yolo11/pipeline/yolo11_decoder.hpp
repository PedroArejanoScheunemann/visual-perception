#pragma once

#include <cstddef>
#include "domain/tensor.hpp"
#include "person_detections.hpp"

namespace vp
{

/**
 * @brief Decodes the output tensor of a YOLO11 model.
 */
class Yolo11Decoder
{
public:

    /**
     * @brief Constructs a YOLO11 decoder.
     *
     * @param output Output tensor.
     * @param detections Output detections.
     */
    Yolo11Decoder(Tensor& output, PersonDetections& detections);

    /**
     * @brief Decodes the output tensor.
     */
    void Process() const;

private:

    Tensor& output_;
    PersonDetections& detections_;
    std::size_t prediction_count_;
    std::size_t prediction_size_;
};

} // namespace vp
