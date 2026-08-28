#include "yolo11_decoder.hpp"

#include <algorithm>
#include <stdexcept>

namespace vp
{

Yolo11Decoder::Yolo11Decoder(Tensor& output) :
                             output_(output),
                             bound_detections_(&detections_)
{
    ValidateOutput();
}

void Yolo11Decoder::Bind(ObjectDetections& detections)
{
    bound_detections_ = &detections;
}

void Yolo11Decoder::Process(const ImageTransform& transform)
{
    bound_detections_->Clear();

    Decode(transform);

    bound_detections_->ApplyNMS(kNMSThreshold);
}

const ObjectDetections& Yolo11Decoder::Detections() const
{
    return *bound_detections_;
}

void Yolo11Decoder::ValidateOutput() const
{
    const TensorSpecification& specification = output_.Specification();

    if (specification.Rank() != 3)
    {
        throw std::invalid_argument("YOLO11 output tensor must have rank 3.");
    }

    if (specification.Dimension(0) != 1)
    {
        throw std::invalid_argument("YOLO11 decoder only supports batch size 1.");
    }

    if (specification.Dimension(1) != kBoxValues + kClassCount)
    {
        throw std::invalid_argument("Unexpected YOLO11 output channel count.");
    }

    if (specification.Type() != TensorType::Float32)
    {
        throw std::invalid_argument("YOLO11 output tensor must use Float32.");
    }
}

void Yolo11Decoder::Decode(const ImageTransform& transform)
{
    const std::size_t candidate_count = output_.Specification().Dimension(2);
    const float* data = static_cast<const float*>(output_.Data());

    // YOLO output layout:
    //
    // [1, 84, 8400]
    //
    // The tensor is channel-first:
    //
    // data[0 * candidate_count + i] -> cx
    // data[1 * candidate_count + i] -> cy
    // data[2 * candidate_count + i] -> width
    // data[3 * candidate_count + i] -> height
    //
    // data[(4 + class_id) * candidate_count + i] -> class confidence

    for (std::size_t i = 0; i < candidate_count; ++i)
    {
        const float center_x = data[i];
        const float center_y = data[candidate_count + i];
        const float width = data[2 * candidate_count + i];
        const float height = data[3 * candidate_count + i];

        const float confidence = data[(kBoxValues + kPersonClass) * candidate_count + i];

        if (confidence < kConfidenceThreshold)
        {
            continue;
        }

        const BoundingBox model_box { .x = center_x - width * 0.5F,
                                      .y = center_y - height * 0.5F,
                                      .width = width,
                                      .height = height };

        ObjectDetection detection;
        detection.bounding_box = transform.ToOriginal(model_box);
        detection.confidence = confidence;

        bound_detections_->Add(detection);
    }
}

} // namespace vp
