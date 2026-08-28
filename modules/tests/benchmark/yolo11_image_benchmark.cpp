#include <algorithm>
#include <filesystem>
#include <fstream>
#include <vector>

#include <gtest/gtest.h>

#include <opencv2/imgcodecs.hpp>

#include "benchmark_reporter.hpp"
#include "engine.hpp"
#include "frame_adapter.hpp"
#include "object_detection_visualizer.hpp"

namespace vp
{
namespace
{

constexpr std::size_t kIterations = 100;
const std::filesystem::path kImagesDirectory = std::filesystem::path(VP_IMAGES_DIR);
const std::filesystem::path kBenchmarkDirectory = std::filesystem::path(VP_BENCHMARK_OUTPUT_DIR) / "yolo11_image";
const std::filesystem::path kReportPath = kBenchmarkDirectory / "report.txt";

} // namespace

TEST(Yolo11ImageBenchmark, ProfileAllImages)
{
    std::filesystem::create_directories(kBenchmarkDirectory);

    std::ofstream report(kReportPath);

    ASSERT_TRUE(report.is_open());

    BenchmarkReporter reporter(report);

    reporter.WriteHeader({
        .name = "YOLO11 IMAGE BENCHMARK",
        .model = "YOLO11n",
        .backend = "ONNX Runtime",
        .iterations = kIterations
    });

    std::vector<std::filesystem::path> image_paths;

    for (const auto& entry : std::filesystem::directory_iterator(kImagesDirectory))
    {
        if (entry.is_regular_file())
        {
            image_paths.push_back(entry.path());
        }
    }

    std::sort(image_paths.begin(), image_paths.end());

    ASSERT_FALSE(image_paths.empty());

    Engine engine;

    engine.AddModel({
        .category = DetectionCategory::Object,
        .backend = BackendType::Onnx,
        .model = ModelType::Yolo11n
    });

    for (std::size_t index = 0; index < image_paths.size(); ++index)
    {
        const std::filesystem::path& image_path = image_paths[index];

        const cv::Mat image = cv::imread(image_path.string(), cv::IMREAD_COLOR);

        ASSERT_FALSE(image.empty());

        const Frame frame = AsFrame(image);

        engine.ResetProfiling();

        for (std::size_t iteration = 0; iteration < kIterations; ++iteration)
        {
            engine.Process(frame);
        }

        reporter.WriteImageBenchmark(index + 1,
                                     image_paths.size(),
                                     image_path,
                                     image,
                                     engine.GetProfileResults());

        const cv::Mat result = ObjectDetectionVisualizer::Draw(image, engine.Detections());

        const std::filesystem::path output_path = kBenchmarkDirectory / (image_path.stem().string() + "_detections" + image_path.extension().string());

        ASSERT_TRUE(cv::imwrite(output_path.string(), result));
    }

    ASSERT_TRUE(report);
}

} // namespace vp
