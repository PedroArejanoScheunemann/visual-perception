#include "benchmark_reporter.hpp"

#include <iomanip>
#include <opencv2/core/version.hpp>
#include <sstream>
#include <string>

namespace vp
{
namespace
{

constexpr std::size_t kSeparatorWidth = 80;

/**
 * @brief Formats a file size as a human-readable string.
 *
 * @param size File size in bytes.
 *
 * @return Formatted file size.
 */
std::string FormatFileSize(std::uintmax_t size)
{
    std::ostringstream stream;

    stream << std::fixed
           << std::setprecision(2);

    if (size < 1024)
    {
        stream << size
               << " B";
    }
    else if (size < 1024 * 1024)
    {
        stream << static_cast<double>(size) / 1024.0
               << " KB";
    }
    else
    {
        stream << static_cast<double>(size) / (1024.0 * 1024.0)
               << " MB";
    }

    return stream.str();
}

/**
 * @brief Returns the OpenCV image type as a readable string.
 *
 * @param image OpenCV image.
 *
 * @return Image type description.
 */
std::string GetImageType(const cv::Mat& image)
{
    std::string depth;

    switch (image.depth())
    {
        case CV_8U:
            depth = "8U";
            break;

        case CV_8S:
            depth = "8S";
            break;

        case CV_16U:
            depth = "16U";
            break;

        case CV_16S:
            depth = "16S";
            break;

        case CV_32S:
            depth = "32S";
            break;

        case CV_32F:
            depth = "32F";
            break;

        case CV_64F:
            depth = "64F";
            break;

        default:
            depth = "Unknown";
            break;
    }

    return "CV_" +
           depth +
           "C" +
           std::to_string(image.channels());
}

/**
 * @brief Returns a readable image color format.
 *
 * @param image OpenCV image.
 *
 * @return Color format description.
 */
std::string GetColorFormat(const cv::Mat& image)
{
    switch (image.channels())
    {
        case 1:
            return "Grayscale";

        case 3:
            return "BGR";

        case 4:
            return "BGRA";

        default:
            return "Unknown";
    }
}

} // namespace

BenchmarkReporter::BenchmarkReporter(std::ostream& stream) :
                                     stream_(stream)
{
}

void BenchmarkReporter::WriteHeader(const BenchmarkConfiguration& configuration)
{
    WriteSeparator();

    stream_ << configuration.name
            << '\n';

    WriteSeparator();

    stream_ << '\n';

    stream_ << "BENCHMARK CONFIGURATION"
            << '\n';

    stream_ << "--------------------------------------------------------------------------------"
            << '\n';

    stream_ << std::left
            << std::setw(25) << "Model"
            << ": "
            << configuration.model
            << '\n';

    stream_ << std::left
            << std::setw(25) << "Backend"
            << ": "
            << configuration.backend
            << '\n';

    stream_ << std::left
            << std::setw(25) << "Iterations"
            << ": "
            << configuration.iterations
            << '\n';

    stream_ << std::left
            << std::setw(25) << "OpenCV Version"
            << ": "
            << CV_VERSION
            << '\n';

    stream_ << '\n';
}

void BenchmarkReporter::WriteImageBenchmark(std::size_t index, std::size_t total, const std::filesystem::path& image_path, const cv::Mat& image, const ProfileResults& results)
{
    WriteItemHeader(index, total);

    WriteImageInformation(image_path, image);

    WritePerformanceResults(results);

    WritePipelineSummary(results);
}

void BenchmarkReporter::WriteItemHeader(std::size_t index, std::size_t total)
{
    WriteSeparator();

    stream_ << "INPUT "
            << index
            << " / "
            << total
            << '\n';

    WriteSeparator();

    stream_ << '\n';
}

void BenchmarkReporter::WriteImageInformation(const std::filesystem::path& image_path, const cv::Mat& image)
{
    stream_ << "IMAGE INFORMATION"
            << '\n';

    stream_ << "--------------------------------------------------------------------------------"
            << '\n';

    const double aspect_ratio = static_cast<double>(image.cols) / static_cast<double>(image.rows);

    stream_ << std::left
            << std::setw(25) << "File"
            << ": "
            << image_path.filename().string()
            << '\n';

    stream_ << std::left
            << std::setw(25) << "Resolution"
            << ": "
            << image.cols
            << " x "
            << image.rows
            << '\n';

    stream_ << std::left
            << std::setw(25) << "Total Pixels"
            << ": "
            << image.total()
            << '\n';

    stream_ << std::left
            << std::setw(25) << "Aspect Ratio"
            << ": "
            << std::fixed
            << std::setprecision(3)
            << aspect_ratio
            << '\n';

    stream_ << std::left
            << std::setw(25) << "Channels"
            << ": "
            << image.channels()
            << '\n';

    stream_ << std::left
            << std::setw(25) << "Color Format"
            << ": "
            << GetColorFormat(image)
            << '\n';

    stream_ << std::left
            << std::setw(25) << "Pixel Type"
            << ": "
            << GetImageType(image)
            << '\n';

    stream_ << std::left
            << std::setw(25) << "File Size"
            << ": "
            << FormatFileSize(std::filesystem::file_size(image_path))
            << '\n';

    stream_ << '\n';
}

void BenchmarkReporter::WritePerformanceResults(const ProfileResults& results)
{
    stream_ << "PERFORMANCE RESULTS"
            << '\n';

    stream_ << "--------------------------------------------------------------------------------"
            << '\n';

    Profiler::WriteReport(stream_, results);

    stream_ << '\n';
}

void BenchmarkReporter::WritePipelineSummary(const ProfileResults& results)
{
    const ProfileStatistics& pipeline = results[ToIndex(ProfileOperation::Pipeline)];

    if (pipeline.count == 0)
    {
        return;
    }

    const double average_latency_ms = pipeline.Average();
    const double throughput_fps = 1000.0 / average_latency_ms;

    stream_ << "PIPELINE SUMMARY"
            << '\n';

    stream_ << "--------------------------------------------------------------------------------"
            << '\n';

    stream_ << std::fixed
            << std::setprecision(3);

    stream_ << std::left
            << std::setw(25) << "Average Latency"
            << ": "
            << average_latency_ms
            << " ms"
            << '\n';

    stream_ << std::left
            << std::setw(25) << "Throughput"
            << ": "
            << throughput_fps
            << " FPS"
            << '\n';

    stream_ << '\n';
}

void BenchmarkReporter::WriteSeparator()
{
    stream_ << std::string(kSeparatorWidth, '=')
            << '\n';
}

} // namespace vp
