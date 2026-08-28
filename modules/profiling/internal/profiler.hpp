#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <limits>
#include <string_view>

namespace vp
{

/**
 * @brief Identifies a profiled pipeline operation.
 *
 * The declaration order defines the order used when reporting profiling
 * results.
 */
enum class ProfileOperation : std::uint8_t
{
    Preprocess,
    Inference,
    Decode,
    Pipeline,

    Count
};

/**
 * @brief Converts a profiling operation to its display name.
 *
 * @param operation Profiling operation.
 *
 * @return Operation name.
 */
constexpr std::string_view ToString(ProfileOperation operation)
{
    switch (operation)
    {
        case ProfileOperation::Preprocess:
            return "preprocess";

        case ProfileOperation::Inference:
            return "inference";

        case ProfileOperation::Decode:
            return "decode";

        case ProfileOperation::Pipeline:
            return "pipeline";

        case ProfileOperation::Count:
            break;
    }

    return "unknown";
}

/**
 * @brief Converts a profiling operation to its array index.
 *
 * @param operation Profiling operation.
 *
 * @return Array index associated with the operation.
 */
constexpr std::size_t ToIndex(ProfileOperation operation)
{
    return static_cast<std::size_t>(operation);
}

/**
 * @brief Stores timing statistics for a profiling operation.
 */
struct ProfileStatistics
{
    /**
     * @brief Number of recorded measurements.
     */
    std::size_t count = 0;

    /**
     * @brief Minimum measured duration in milliseconds.
     */
    double min_ms = std::numeric_limits<double>::max();

    /**
     * @brief Accumulated duration in milliseconds.
     */
    double total_ms = 0.0;

    /**
     * @brief Maximum measured duration in milliseconds.
     */
    double max_ms = 0.0;

    /**
     * @brief Records a new duration measurement.
     *
     * @param duration_ms Duration in milliseconds.
     */
    void Record(double duration_ms);

    /**
     * @brief Returns the average duration in milliseconds.
     *
     * @return Average duration.
     */
    double Average() const;

    /**
     * @brief Resets all statistics.
     */
    void Reset();
};

/**
 * @brief Collection of profiling results.
 *
 * Results are stored in the same order as ProfileOperation.
 */
using ProfileResults = std::array<ProfileStatistics, ToIndex(ProfileOperation::Count)>;

/**
 * @brief Collects execution-time measurements.
 *
 * The profiler provides a single shared instance used by the perception
 * pipeline.
 */
class Profiler
{
public:

    /**
     * @brief Returns the shared profiler instance.
     *
     * @return Shared profiler.
     */
    static Profiler& Get();

    /**
     * @brief Records an execution duration.
     *
     * @param operation Profiled operation.
     * @param duration Execution duration.
     */
    void Record(ProfileOperation operation, std::chrono::nanoseconds duration);

    /**
     * @brief Returns all profiling results.
     *
     * @return Constant reference to the collected results.
     */
    const ProfileResults& GetResults() const;

    /**
     * @brief Writes profiling results to a text stream.
     *
     * @param stream Output stream.
     * @param results Profiling results to write.
     *
     * @throws std::runtime_error if the stream cannot be written.
     */
    static void WriteReport(std::ostream& stream, const ProfileResults& results);

    /**
     * @brief Writes the collected profiling results to a text stream.
     *
     * @param stream Output stream.
     */
    void WriteReport(std::ostream& stream) const;

    /**
     * @brief Removes all recorded measurements.
     */
    void Reset();

    /**
     * @brief Copy construction is disabled.
     */
    Profiler(const Profiler&) = delete;

    /**
     * @brief Copy assignment is disabled.
     *
     * @return Reference to this object.
     */
    Profiler& operator=(const Profiler&) = delete;

private:

    Profiler() = default;

private:

    ProfileResults results_;
};

/**
 * @brief Measures the lifetime of a scope using RAII.
 *
 * The timer starts when the object is constructed and automatically records
 * the elapsed time in the shared profiler when the scope is exited.
 */
class ScopedTimer
{
public:

    /**
     * @brief Starts a scoped measurement.
     *
     * @param operation Profiled operation.
     */
    explicit ScopedTimer(ProfileOperation operation);

    /**
     * @brief Stops the measurement and records the elapsed time.
     */
    ~ScopedTimer();

    /**
     * @brief Copy construction is disabled.
     */
    ScopedTimer(const ScopedTimer&) = delete;

    /**
     * @brief Copy assignment is disabled.
     *
     * @return Reference to this object.
     */
    ScopedTimer& operator=(const ScopedTimer&) = delete;

private:

    ProfileOperation operation_;

    std::chrono::steady_clock::time_point start_;
};

} // namespace vp
