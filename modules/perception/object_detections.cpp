#include "object_detections.hpp"
#include <algorithm>

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

bool ObjectDetections::Empty() const
{
    return detections_.empty();
}

void ObjectDetections::SortByConfidence()
{
    std::sort(detections_.begin(),
              detections_.end(),
              [](const ObjectDetection& first, const ObjectDetection& second)
              {
                  return first.confidence > second.confidence;
              });
}

void ObjectDetections::ApplyNMS(float iou_threshold)
{
    SortByConfidence();

    for (std::size_t i = 0; i < detections_.size(); ++i)
    {
        for (std::size_t j = i + 1; j < detections_.size();)
        {
            if (IoU(detections_[i].bounding_box, detections_[j].bounding_box) > iou_threshold)
            {
                detections_.erase(detections_.begin() + j);
            }
            else
            {
                ++j;
            }
        }
    }
}

float ObjectDetections::IoU(const BoundingBox& first, const BoundingBox& second)
{
    const float first_left = first.x;
    const float first_top = first.y;
    const float first_right = first.x + first.width;
    const float first_bottom = first.y + first.height;

    const float second_left = second.x;
    const float second_top = second.y;
    const float second_right = second.x + second.width;
    const float second_bottom = second.y + second.height;

    const float intersection_left = std::max(first_left, second_left);
    const float intersection_top = std::max(first_top, second_top);
    const float intersection_right = std::min(first_right, second_right);
    const float intersection_bottom = std::min(first_bottom, second_bottom);
    const float intersection_width = std::max(0.0F, intersection_right - intersection_left);
    const float intersection_height = std::max(0.0F, intersection_bottom - intersection_top);
    const float intersection_area = intersection_width * intersection_height;

    const float first_area = std::max(0.0F, first.width) * std::max(0.0F, first.height);
    const float second_area = std::max(0.0F, second.width) * std::max(0.0F, second.height);
    const float union_area = first_area + second_area - intersection_area;

    if (union_area <= 0.0F)
    {
        return 0.0F;
    }

    return intersection_area / union_area;
}

const std::vector<ObjectDetection>& ObjectDetections::Get() const
{
    return detections_;
}

} // namespace vp
