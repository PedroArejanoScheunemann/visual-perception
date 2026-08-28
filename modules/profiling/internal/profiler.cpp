#include "profiler.hpp"

#include <iomanip>
#include <stdexcept>

namespace vp
{

void ProfileStatistics::Record(double duration_ms)
{
    ++count;

    total_ms += duration_ms;

    if (duration_ms < min_ms)
    {
        min_ms = duration_ms;
    }

    if (duration_ms > max_ms)
    {
        max_ms = duration_ms;
    }
}

double ProfileStatistics::Average() const
{
    if (count == 0)
    {
        return 0.0;
    }

    return total_ms / static_cast<double>(count);
}

void ProfileStatistics::Reset()
{
    count = 0;
    min_ms = std::numeric_limits<double>::max();
    total_ms = 0.0;
    max_ms = 0.0;
}

Profiler& Profiler::Get()
{
    static Profiler profiler;

    return profiler;
}

void Profiler::Record(ProfileOperation operation, std::chrono::nanoseconds duration)
{
    const double duration_ms = static_cast<double>(duration.count()) / 1'000'000.0;

    ProfileStatistics& statistics = results_[ToIndex(operation)];

    statistics.Record(duration_ms);
}

const ProfileResults& Profiler::GetResults() const
{
    return results_;
}

void Profiler::WriteReport(std::ostream& stream, const ProfileResults& results)
{
    stream << std::left
           << std::setw(20) << "Operation"
           << std::right
           << std::setw(15) << "Min (ms)"
           << std::setw(15) << "Average (ms)"
           << std::setw(15) << "Max (ms)"
           << std::setw(12) << "Count"
           << '\n';

    stream << "--------------------------------------------------------------------------------"
           << '\n';

    stream << std::fixed
           << std::setprecision(3);

    for (std::size_t index = 0; index < results.size(); ++index)
    {
        const ProfileOperation operation = static_cast<ProfileOperation>(index);
        const ProfileStatistics& statistics = results[index];

        if (statistics.count == 0)
        {
            continue;
        }

        stream << std::left
               << std::setw(20) << ToString(operation)
               << std::right
               << std::setw(15) << statistics.min_ms
               << std::setw(15) << statistics.Average()
               << std::setw(15) << statistics.max_ms
               << std::setw(12) << statistics.count
               << '\n';
    }

    if (!stream)
    {
        throw std::runtime_error("Failed to write profiling report.");
    }
}

void Profiler::WriteReport(std::ostream& stream) const
{
    WriteReport(stream, results_);
}

void Profiler::Reset()
{
    for (ProfileStatistics& statistics : results_)
    {
        statistics.Reset();
    }
}

ScopedTimer::ScopedTimer(ProfileOperation operation) :
                         operation_(operation),
                         start_(std::chrono::steady_clock::now())
{
}

ScopedTimer::~ScopedTimer()
{
    const auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start_);
    Profiler::Get().Record(operation_, duration);
}

} // namespace vp
