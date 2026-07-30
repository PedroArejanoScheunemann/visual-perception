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
     * @brief Returns all detections.
     *
     * @return Collection of detections.
     */
    const std::vector<ObjectDetection>& Get() const;

private:

    std::vector<ObjectDetection> detections_;
};

} // namespace vp
