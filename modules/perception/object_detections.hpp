#pragma once

#include <vector>

#include "object_detection.hpp"

namespace vp
{

/**
 * @brief Collection of detected people.
 */
class ObjectDetections
{
public:

    /**
     * @brief Removes all detections.
     */
    void Clear();

    /**
     * @brief Adds a detected object.
     *
     * @param detection Detection to add.
     */
    void Add(const ObjectDetection& detection);

    /**
     * @brief Checks whether the collection contains no detections.
     *
     * @return True if there are no detections, false otherwise.
     */
    bool Empty() const;

    /**
    * @brief Sorts detections by confidence in descending order.
    */
    void SortByConfidence();

    /**
    * @brief Applies non-maximum suppression.
    *
    * Detections must be sorted by confidence in descending order.
    *
    * @param iou_threshold IoU threshold used to suppress overlapping detections.
    */
    void ApplyNMS(float iou_threshold);

    /**
     * @brief Returns all detections.
     *
     * @return Collection of detections.
     */
    const std::vector<ObjectDetection>& Get() const;

private:
    /**
    * @brief Calculates the intersection over union of two bounding boxes.
    *
    * @param first First bounding box.
    * @param second Second bounding box.
    *
    * @return Intersection over union.
    */
    static float IoU(const BoundingBox& first, const BoundingBox& second);

private:

    std::vector<ObjectDetection> detections_;
};

} // namespace vp
