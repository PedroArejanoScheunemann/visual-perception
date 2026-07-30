#include "yolo11_object_detector.hpp"

namespace vp
{

Yolo11ObjectDetector::Yolo11ObjectDetector(std::unique_ptr<Backend> backend) :
                                           backend_(std::move(backend)),
                                           preprocessor_(backend_->Inputs()),
                                           decoder_(backend_->Outputs())
{
}

void Yolo11ObjectDetector::Process(const Frame& frame)
{
    preprocessor_.Process(frame);

    backend_->Infer();

    decoder_.Process();
}

void Yolo11ObjectDetector::OnBind()
{
    decoder_.Bind(Detections());
}

} // namespace vp
