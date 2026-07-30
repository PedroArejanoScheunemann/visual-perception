#pragma once

#include <vector>

#include "object_detections.hpp"
#include "tensor.hpp"

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
     * @param outputs Output tensors.
     */
    explicit Yolo11Decoder(std::vector<Tensor>& outputs);

    /**
     * @brief Binds the destination where decoded detections are stored.
     *
     * By default, the decoder stores detections internally. Calling Bind()
     * redirects the output to the provided object detections.
     *
     * @param detections Destination for decoded detections.
     */
    void Bind(ObjectDetections& detections);

    /**
     * @brief Decodes the output tensor.
     */
    void Process();

    /**
     * @brief Returns the decoded object detections.
     *
     * Returns either the internally stored detections or the bound destination,
     * depending on whether Bind() has been called.
     *
     * @return Object detections.
     */
    const ObjectDetections& Detections() const;

private:

    std::vector<Tensor>& outputs_;

    ObjectDetections detections_;

    ObjectDetections* bound_detections_;
};

} // namespace vp
