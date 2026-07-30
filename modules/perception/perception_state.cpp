#include "perception_state.hpp"

namespace vp
{

void PerceptionState::Clear()
{
    object_detections_.Clear();
}

ObjectDetections& PerceptionState::Detections()
{
    return object_detections_;
}

const ObjectDetections& PerceptionState::Detections() const
{
    return object_detections_;
}

} // namespace vp
