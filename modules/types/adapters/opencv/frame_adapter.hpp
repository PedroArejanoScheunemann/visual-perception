#pragma once

#include <opencv2/core/mat.hpp>

#include "frame.hpp"

namespace vp
{

/**
 * @brief Creates a Frame view from an OpenCV image.
 *
 * The returned Frame references the pixel buffer owned by the supplied
 * cv::Mat. No image data is copied.
 *
 * The caller must ensure that the cv::Mat remains valid while the returned
 * Frame is being used.
 *
 * Supported formats:
 * - CV_8UC1 -> PixelFormat::Gray8
 * - CV_8UC3 -> PixelFormat::BGR888
 * - CV_8UC4 -> PixelFormat::BGRA8888
 *
 * @param image OpenCV image.
 *
 * @return Frame referencing the OpenCV image buffer.
 *
 * @throws std::invalid_argument if the image format is unsupported.
 */
Frame AsFrame(const cv::Mat& image);

} // namespace vp
