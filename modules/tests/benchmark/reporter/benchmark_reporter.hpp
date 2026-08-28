#pragma once

#include <cstddef>
#include <filesystem>
#include <iosfwd>
#include <string_view>

#include <opencv2/core/mat.hpp>

#include "profiler.hpp"

namespace vp
{

/**
 * @brief Describes a benchmark configuration.
 */
struct BenchmarkConfiguration
{
    /**
     * @brief Benchmark name.
     */
    std::string_view name;

    /**
     * @brief Model name.
     */
    std::string_view model;

    /**
     * @brief Inference backend name.
     */
    std::string_view backend;

    /**
     * @brief Number of benchmark iterations.
     */
    std::size_t iterations;
};

/**
 * @brief Formats benchmark reports.
 *
 * Provides a consistent report format for performance benchmarks,
 * including benchmark configuration, input information and profiling
 * summaries.
 */
class BenchmarkReporter
{
public:

    /**
     * @brief Creates a benchmark reporter.
     *
     * @param stream Output stream.
     */
    explicit BenchmarkReporter(std::ostream& stream);

    /**
     * @brief Writes the benchmark header and configuration.
     *
     * @param configuration Benchmark configuration.
     */
    void WriteHeader(const BenchmarkConfiguration& configuration);

    /**
     * @brief Writes a complete image benchmark result.
     *
     * Includes input information, profiling results and pipeline summary.
     *
     * @param index Current image index.
     * @param total Total number of images.
     * @param image_path Input image path.
     * @param image Input image.
     * @param results Profiling results.
     */
    void WriteImageBenchmark(std::size_t index,
                             std::size_t total,
                             const std::filesystem::path& image_path,
                             const cv::Mat& image,
                             const ProfileResults& results);

private:

    void WriteItemHeader(std::size_t index, std::size_t total);

    void WriteImageInformation(const std::filesystem::path& image_path, const cv::Mat& image);

    void WritePerformanceResults(const ProfileResults& results);

    void WritePipelineSummary(const ProfileResults& results);

    void WriteSeparator();

private:

    std::ostream& stream_;
};

} // namespace vp
