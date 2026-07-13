#pragma once

#include <cstdint>
#include "size.hpp"

namespace vp
{

/**
 * @brief Pixel format.
 */
enum class PixelFormat : uint8_t
{
    Unknown,
    RGB888,
    BGR888,
    RGBA8888,
    BGRA8888,
    Gray8
};

/**
 * @brief Generic image representation.
 *
 * This type does not own the image memory.
 */
struct Image
{
    /**
     * Pointer to the first pixel.
     */
    const void* data{nullptr};

    /**
     * Image size.
     */
    Size size;

    /**
     * Image pixel format.
     */
    PixelFormat pixel_format{PixelFormat::Unknown};

    /**
     * Bytes between consecutive image rows.
     */
    uint32_t stride{0};
};

} // namespace vp
