#pragma once

#include <vector>

#include "image_transform.hpp"
#include "object_detections.hpp"
#include "tensor.hpp"

namespace vp
{

/**
 * @brief Decodes YOLO11 object detection outputs.
 */
class Yolo11Decoder
{
public:

    /**
     * @brief Constructs a YOLO11 decoder.
     *
     * @param output Output tensor produced by the inference backend.
     */
    explicit Yolo11Decoder(Tensor& output);

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
     * @brief Decodes the model output.
     *
     * @param transform Transformation applied during preprocessing.
     */
    void Process(const ImageTransform& transform);

    /**
     * @brief Returns the decoded detections.
     *
     * Bounding boxes are returned in the coordinate system of the original input frame.
     *
     * @return Decoded object detections.
     */
    const ObjectDetections& Detections() const;

private:

    static constexpr std::size_t kBoxValues = 4;
    static constexpr std::size_t kClassCount = 80;
    static constexpr std::size_t kPersonClass = 0;

    static constexpr float kConfidenceThreshold = 0.25F;
    static constexpr float kNMSThreshold = 0.45F;

    void ValidateOutput() const;

    void Decode(const ImageTransform& transform);

    static float IoU(const BoundingBox& first, const BoundingBox& second);

private:

    Tensor& output_;

    ObjectDetections detections_;

    ObjectDetections* bound_detections_;
};

} // namespace vp
