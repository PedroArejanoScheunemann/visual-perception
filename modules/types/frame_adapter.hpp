#pragma once

#include "frame.hpp"

namespace vp
{

/**
 * @brief Converts an object to a Frame.
 *
 * @param frame Frame to adapt.
 *
 * @return Reference to the input frame.
 */
inline const Frame& AsFrame(const Frame& frame)
{
    return frame;
}

} // namespace vp
