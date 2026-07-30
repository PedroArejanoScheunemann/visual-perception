#include "yolo11_decoder.hpp"

namespace vp
{

Yolo11Decoder::Yolo11Decoder(std::vector<Tensor>& outputs) :
    outputs_(outputs),
    bound_detections_(&detections_)
{
}

void Yolo11Decoder::Bind(ObjectDetections& detections)
{
    bound_detections_ = &detections;
}

void Yolo11Decoder::Process()
{
    bound_detections_->Clear();

    //
    // TODO:
    // Decode outputs_ and populate *bound_detections_.
    //
}

const ObjectDetections& Yolo11Decoder::Detections() const
{
    return *bound_detections_;
}

} // namespace vp
