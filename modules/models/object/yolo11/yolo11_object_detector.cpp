#include "yolo11_object_detector.hpp"

namespace vp
{

Yolo11ObjectDetector::Yolo11ObjectDetector(std::unique_ptr<Backend> backend) :
                                           backend_(std::move(backend)),
                                           preprocessor_(backend_->Inputs().front()),
                                           decoder_(backend_->Outputs().front())
{
}

void Yolo11ObjectDetector::Process(const Frame& frame)
{
    const ImageTransform transform = preprocessor_.Process(frame);

    backend_->Infer();

    decoder_.Process(transform);
}

void Yolo11ObjectDetector::OnBind()
{
    decoder_.Bind(Detections());
}

} // namespace vp
