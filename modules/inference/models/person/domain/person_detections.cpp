#include "person_detections.hpp"

namespace vp
{

void PersonDetections::Clear()
{
    detections_.clear();
}

void PersonDetections::Add(const PersonDetection& detection)
{
    detections_.push_back(detection);
}

const std::vector<PersonDetection>& PersonDetections::Get() const
{
    return detections_;
}

} // namespace vp
