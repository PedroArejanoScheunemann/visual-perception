#include "yolo11_preprocessor.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <stdexcept>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

namespace vp
{
namespace
{

cv::Mat CreateImage(const Frame& frame)
{
    if (frame.image.data == nullptr)
    {
        throw std::invalid_argument("Frame contains no image data.");
    }

    const int width = static_cast<int>(frame.image.size.width);
    const int height = static_cast<int>(frame.image.size.height);

    if (width <= 0 || height <= 0)
    {
        throw std::invalid_argument("Frame has invalid dimensions.");
    }

    void* data = const_cast<void*>(frame.image.data);

    switch (frame.image.pixel_format)
    {
        case PixelFormat::RGB888:
        case PixelFormat::BGR888:
            return cv::Mat(height,
                           width,
                           CV_8UC3,
                           data,
                           static_cast<std::size_t>(frame.image.stride));

        case PixelFormat::RGBA8888:
        case PixelFormat::BGRA8888:
            return cv::Mat(height,
                          width,
                          CV_8UC4,
                          data,
                          static_cast<std::size_t>(frame.image.stride));

        case PixelFormat::Gray8:
            return cv::Mat(height,
                          width,
                          CV_8UC1,
                          data,
                          static_cast<std::size_t>(frame.image.stride));

        default:
            throw std::invalid_argument("Unsupported frame pixel format.");
    }
}

cv::Mat ConvertToRGB(const cv::Mat& image, PixelFormat pixel_format)
{
    cv::Mat rgb;

    switch (pixel_format)
    {
        case PixelFormat::RGB888:
            rgb = image;
            break;

        case PixelFormat::BGR888:
            cv::cvtColor(image, rgb, cv::COLOR_BGR2RGB);
            break;

        case PixelFormat::RGBA8888:
            cv::cvtColor(image, rgb, cv::COLOR_RGBA2RGB);
            break;

        case PixelFormat::BGRA8888:
            cv::cvtColor(image, rgb, cv::COLOR_BGRA2RGB);
            break;

        case PixelFormat::Gray8:
            cv::cvtColor(image, rgb, cv::COLOR_GRAY2RGB);
            break;

        default:
            throw std::invalid_argument("Unsupported frame pixel format.");
    }

    return rgb;
}

cv::Mat Letterbox(const cv::Mat& image, int target_width, int target_height, float& scale, float& padding_x, float& padding_y)
{
    scale = std::min(static_cast<float>(target_width) / static_cast<float>(image.cols),
                     static_cast<float>(target_height) / static_cast<float>(image.rows));

    const int resized_width = static_cast<int>(std::round(static_cast<float>(image.cols) * scale));
    const int resized_height = static_cast<int>(std::round(static_cast<float>(image.rows) * scale));

    cv::Mat resized;

    cv::resize(image,
              resized,
              cv::Size(resized_width, resized_height),
              0.0,
              0.0,
              cv::INTER_LINEAR);

    const int padding_width = target_width - resized_width;
    const int padding_height = target_height - resized_height;
    const int left = padding_width / 2;
    const int right = padding_width - left;
    const int top = padding_height / 2;
    const int bottom = padding_height - top;
    padding_x = static_cast<float>(left);
    padding_y = static_cast<float>(top);

    cv::Mat output;

    cv::copyMakeBorder(resized,
                       output,
                       top,
                       bottom,
                       left,
                       right,
                       cv::BORDER_CONSTANT,
                       cv::Scalar(114, 114, 114));

    return output;
}

void ConvertHwcToChw(const cv::Mat& image, float* destination)
{
    const int width = image.cols;
    const int height = image.rows;

    const std::size_t plane_size = static_cast<std::size_t>(width) * static_cast<std::size_t>(height);

    for (int y = 0; y < height; ++y)
    {
        const cv::Vec3b* row = image.ptr<cv::Vec3b>(y);

        for (int x = 0; x < width; ++x)
        {
            const std::size_t index = static_cast<std::size_t>(y) * static_cast<std::size_t>(width) + static_cast<std::size_t>(x);
            destination[index] = static_cast<float>(row[x][0]) / 255.0F;
            destination[plane_size + index] = static_cast<float>(row[x][1]) / 255.0F;
            destination[2 * plane_size + index] = static_cast<float>(row[x][2]) / 255.0F;
        }
    }
}

} // namespace

Yolo11Preprocessor::Yolo11Preprocessor(Tensor& input) :
                                       input_(input)
{
    ValidateInput();
}

void Yolo11Preprocessor::ValidateInput() const
{
    const TensorSpecification& specification = input_.Specification();

    if (specification.Rank() != 4)
    {
        throw std::invalid_argument("YOLO11 input tensor must have rank 4.");
    }

    if (specification.Type() != TensorType::Float32)
    {
        throw std::invalid_argument("YOLO11 input tensor must use Float32.");
    }

    if (specification.Dimension(0) != 1)
    {
        throw std::invalid_argument("YOLO11 preprocessor only supports batch size 1.");
    }

    if (specification.Dimension(1) != 3)
    {
        throw std::invalid_argument("YOLO11 input tensor must have 3 channels.");
    }

    if (specification.Dimension(2) <= 0 || specification.Dimension(3) <= 0)
    {
        throw std::invalid_argument("YOLO11 input tensor has invalid dimensions.");
    }
}

ImageTransform Yolo11Preprocessor::Process(const Frame& frame) const
{
    const TensorSpecification& specification = input_.Specification();
    const int target_height = static_cast<int>(specification.Dimension(2));
    const int target_width = static_cast<int>(specification.Dimension(3));

    cv::Mat image = CreateImage(frame);
    cv::Mat rgb = ConvertToRGB(image, frame.image.pixel_format);

    float scale = 0.0F;
    float padding_x = 0.0F;
    float padding_y = 0.0F;

    cv::Mat letterboxed = Letterbox(rgb,
                                    target_width,
                                    target_height,
                                    scale,
                                    padding_x,
                                    padding_y);

    float* destination = static_cast<float*>(input_.Data());

    ConvertHwcToChw(letterboxed, destination);

    return ImageTransform(scale, padding_x, padding_y);
}

} // namespace vp
