#pragma once

#include <vector>

#include "person_detection.hpp"

namespace vp
{

/**
 * @brief Collection of detected people.
 */
class PersonDetections
{
public:

    /**
     * @brief Removes all detections.
     */
    void Clear();

    /**
     * @brief Adds a detected person.
     *
     * @param detection Detection to add.
     */
    void Add(const PersonDetection& detection);

    /**
     * @brief Returns all detections.
     *
     * @return Collection of detections.
     */
    const std::vector<PersonDetection>& Get() const;

private:

    std::vector<PersonDetection> detections_;
};

} // namespace vp
