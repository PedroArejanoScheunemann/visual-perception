#pragma once

#ifdef VP_ENABLE_PROFILING

#include "profiler.hpp"

/**
 * @brief Creates a scoped profiling timer.
 *
 * The measurement starts at the beginning of the current scope and is
 * automatically recorded when the scope is exited.
 *
 * @param operation Profile operation.
 */
#define VP_PROFILE_SCOPE(operation) vp::ScopedTimer vp_profile_timer_##__LINE__(operation)

#else

/**
 * @brief Disabled profiling scope.
 *
 * Expands to nothing when profiling is disabled.
 */
#define VP_PROFILE_SCOPE(operation)

#endif
