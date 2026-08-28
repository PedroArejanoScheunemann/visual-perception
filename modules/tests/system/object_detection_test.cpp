#include <filesystem>

#include <gtest/gtest.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include "engine.hpp"
#include "frame_adapter.hpp"

namespace vp
{
namespace
{

TEST(ObjectDetectionSystemTest, DetectsPerson)
{
    const std::filesystem::path image_path =
    std::filesystem::path(VP_IMAGES_DIR) / "3_pessoas.jpeg";

    const cv::Mat image = cv::imread(image_path.string(), cv::IMREAD_COLOR);

    ASSERT_FALSE(image.empty());

    Engine engine;

    engine.AddModel({
        .category = DetectionCategory::Object,
        .backend = BackendType::Onnx,
        .model = ModelType::Yolo11n
    });

    const Frame frame = AsFrame(image);

    ASSERT_NO_THROW(engine.Process(frame));

    const ObjectDetections& detections = engine.Detections();

    ASSERT_FALSE(detections.Empty());

    cv::Mat result = image.clone();

    for (const ObjectDetection& detection : detections.Get())
    {
        const BoundingBox& box = detection.bounding_box;

        const cv::Rect rectangle(static_cast<int>(box.x),
                                 static_cast<int>(box.y),
                                 static_cast<int>(box.width),
                                 static_cast<int>(box.height));

        cv::rectangle(result,
                     rectangle,
                     cv::Scalar(0, 255, 0),
                     2);

        const std::string confidence = std::to_string(detection.confidence);

        cv::putText(result,
                    confidence,
                    cv::Point(rectangle.x,
                              std::max(
                              0,
                              rectangle.y - 5)),
                    cv::FONT_HERSHEY_SIMPLEX,
                    0.5,
                    cv::Scalar(0, 255, 0),
                    1);
    }

    const std::filesystem::path output_path =
    image_path.parent_path() / (image_path.stem().string() + "_detections" + image_path.extension().string());

    ASSERT_TRUE(
        cv::imwrite(
            output_path.string(),
            result));


}

} // namespace
} // namespace vp
