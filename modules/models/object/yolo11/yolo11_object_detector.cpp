#include "yolo11_object_detector.hpp"
#include "profiler_macros.hpp"

namespace vp
{
Yolo11ObjectDetector::Yolo11ObjectDetector(std::unique_ptr<Backend> backend) :
                                           backend_(std::move(backend)),
                                           preprocessor_(backend_->Inputs().front()),
                                           decoder_(backend_->Outputs().front(), preprocessor_.Transform())
{
}

void Yolo11ObjectDetector::Process(const Frame& frame)
{
    {
        VP_PROFILE_SCOPE(ProfileOperation::Preprocess);
        preprocessor_.Process(frame);
    }

    {
        VP_PROFILE_SCOPE(ProfileOperation::Inference);
        backend_->Infer();
    }

    {
        VP_PROFILE_SCOPE(ProfileOperation::Decode);
        decoder_.Process();
    }
}

void Yolo11ObjectDetector::OnBind()
{
    decoder_.Bind(Detections());
}

} // namespace vp
