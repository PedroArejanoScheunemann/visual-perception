#pragma once

#include <cstdint>
#include "image.hpp"

namespace vp {

/**
 * @brief Camera frame.
 */
struct Frame
{
    /**
     * Captured image.
     */
    Image image;

    /**
     * Timestamp in microseconds.
     */
    uint64_t timestamp_us{0};
};

} // namespace vp
