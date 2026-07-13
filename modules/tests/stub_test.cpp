#include <gtest/gtest.h>

#include "engine.hpp"

namespace vp
{

TEST(EngineTest, ProcessFrame)
{
    Frame frame;

    Engine engine;

    engine.Process(frame);

    SUCCEED();
}

} // namespace vp
