#include "frame_adapter.hpp"

#include <stdexcept>

namespace vp
{
namespace
{

PixelFormat ConvertPixelFormat(int type)
{
    switch (type)
    {
        case CV_8UC1:
            return PixelFormat::Gray8;

        case CV_8UC3:
            return PixelFormat::BGR888;

        case CV_8UC4:
            return PixelFormat::BGRA8888;

        default:
            throw std::invalid_argument("Unsupported OpenCV image format.");
    }
}

} // namespace

Frame AsFrame(const cv::Mat& image)
{
    return {
        .image =
        {
            .data = image.data,
            .size =
            {
                static_cast<uint32_t>(image.cols),
                static_cast<uint32_t>(image.rows)
            },
            .pixel_format = ConvertPixelFormat(image.type()),
            .stride = static_cast<uint32_t>(image.step)
        }
    };
}

} // namespace vp
