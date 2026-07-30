#pragma once

#include "object_detections.hpp"

namespace vp
{

/**
 * @brief Stores the current perception results.
 *
 * The perception state is owned by the engine and updated by inference models
 * during processing.
 */
class PerceptionState
{
public:

    /**
     * @brief Clears all stored perception results.
     */
    void Clear();

    /**
     * @brief Returns the current object detections.
     *
     * @return Object detections.
     */
    ObjectDetections& Detections();

    /**
     * @brief Returns the current object detections.
     *
     * @return Object detections.
     */
    const ObjectDetections& Detections() const;

private:

    ObjectDetections object_detections_;
};

} // namespace vp
