#include "object_detection_model.hpp"

namespace vp
{

void ObjectDetectionModel::Bind(ObjectDetections& detections)
{
    detections_ = &detections;
    OnBind();
}

void ObjectDetectionModel::OnBind()
{
}

ObjectDetections& ObjectDetectionModel::Detections()
{
    assert(detections_ != nullptr);

    return *detections_;
}

const ObjectDetections& ObjectDetectionModel::Detections() const
{
    assert(detections_ != nullptr);

    return *detections_;
}

} // namespace vp
