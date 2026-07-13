#include <gtest/gtest.h>

#include "yolo11_person_detector.hpp"

namespace vp
{

TEST(Yolo11PersonDetectorTest, ProcessFrame)
{
    Frame frame;

    Yolo11PersonDetector detector;

    detector.Process(frame);

    SUCCEED();
}

} // namespace vp
