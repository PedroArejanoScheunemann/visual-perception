#pragma once

#include <opencv2/core/mat.hpp>

#include "object_detections.hpp"

namespace vp
{

/**
 * @brief Provides visualization utilities for object detections.
 */
class ObjectDetectionVisualizer
{
public:

    /**
     * @brief Draws object detections on an image.
     *
     * The returned image is a copy of the input image containing the
     * detected bounding boxes and confidence values.
     *
     * @param image Source image.
     * @param detections Object detections to visualize.
     *
     * @return Image containing the rendered detections.
     */
    static cv::Mat Draw(const cv::Mat& image, const ObjectDetections& detections);
};

} // namespace vp
