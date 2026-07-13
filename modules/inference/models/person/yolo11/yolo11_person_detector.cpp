#include "yolo11_person_detector.hpp"

namespace vp
{

Yolo11PersonDetector::Yolo11PersonDetector() :
                                           specification_(yolo11::kPersonDetector),
                                           input_(specification_.input),
                                           output_(specification_.output),
                                           preprocessor_(input_),
                                           decoder_(output_, detections_)
{
}

void Yolo11PersonDetector::Process(const Frame& frame)
{
    preprocessor_.Process(frame);

    // TODO Execute inference backend.

    decoder_.Process();
}

const PersonDetections& Yolo11PersonDetector::Detections() const
{
    return detections_;
}

} // namespace vp
