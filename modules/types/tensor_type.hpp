#pragma once

#include <cstdint>

namespace vp
{

/**
 * @brief Supported tensor element types.
 */
enum class TensorType : std::uint8_t
{
    Float32 = 0,
    Float16,
    Int32,
    Int8,
    UInt8
};

} // namespace vp
