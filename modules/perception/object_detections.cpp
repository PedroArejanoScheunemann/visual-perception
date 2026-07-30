#include "object_detections.hpp"

namespace vp
{

void ObjectDetections::Clear()
{
    detections_.clear();
}

void ObjectDetections::Add(const ObjectDetection& detection)
{
    detections_.push_back(detection);
}

const std::vector<ObjectDetection>& ObjectDetections::Get() const
{
    return detections_;
}

} // namespace vp
