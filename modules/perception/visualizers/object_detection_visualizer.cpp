#include "object_detection_visualizer.hpp"

#include <algorithm>
#include <iomanip>
#include <sstream>

#include <opencv2/imgproc.hpp>

namespace vp
{

cv::Mat ObjectDetectionVisualizer::Draw(const cv::Mat& image, const ObjectDetections& detections)
{
    cv::Mat result = image.clone();

    for (const ObjectDetection& detection : detections.Get())
    {
        const BoundingBox& box = detection.bounding_box;

        const cv::Rect image_bounds(0, 0, result.cols, result.rows);

        const cv::Rect bounding_box(static_cast<int>(box.x),
                                    static_cast<int>(box.y),
                                    static_cast<int>(box.width),
                                    static_cast<int>(box.height));

        const cv::Rect rectangle = bounding_box & image_bounds;

        if (rectangle.empty())
        {
            continue;
        }

        cv::rectangle(result,
                      rectangle,
                      cv::Scalar(0, 255, 0),
                      2);

        std::ostringstream confidence_stream;

        confidence_stream << std::fixed << std::setprecision(2) << detection.confidence;

        const std::string label = confidence_stream.str();

        const cv::Point label_position(rectangle.x, std::max(0, rectangle.y - 5));

        cv::putText(result,
                    label,
                    label_position,
                    cv::FONT_HERSHEY_SIMPLEX,
                    0.5,
                    cv::Scalar(0, 255, 0),
                    1);
    }

    return result;
}

} // namespace vp
