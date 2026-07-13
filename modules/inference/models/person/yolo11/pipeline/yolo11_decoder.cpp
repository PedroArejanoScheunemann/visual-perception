#include "yolo11_decoder.hpp"

namespace vp
{

Yolo11Decoder::Yolo11Decoder(Tensor& output, PersonDetections& detections) :
                             output_(output),
                             detections_(detections),
                             prediction_count_(output.Descriptor().Width()),
                             prediction_size_(output.Descriptor().Channels())
{
}

void Yolo11Decoder::Process() const
{
    detections_.Clear();

    // TODO
    //
    // Decode the output tensor into detections.
}

} // namespace vp
