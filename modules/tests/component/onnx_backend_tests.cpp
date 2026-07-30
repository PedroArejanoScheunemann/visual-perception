#include <filesystem>

#include <gtest/gtest.h>

#include "onnx_backend.hpp"

namespace vp
{
namespace
{

const std::filesystem::path kModelPath =
    std::filesystem::path(VP_ASSETS_DIR) /
    "weights" /
    "object" /
    "yolo11n.onnx";

} // namespace

class OnnxBackendTest : public ::testing::Test
{
protected:

    OnnxBackend backend;
};

TEST_F(OnnxBackendTest, LoadInvalidModel)
{
    EXPECT_FALSE(backend.LoadModel("invalid.onnx"));
}

TEST_F(OnnxBackendTest, LoadValidModel)
{
    EXPECT_TRUE(backend.LoadModel(kModelPath));
}

TEST_F(OnnxBackendTest, Input)
{
    ASSERT_TRUE(backend.LoadModel(kModelPath));

    const std::vector<Tensor>& inputs = backend.Inputs();

    ASSERT_EQ(inputs.size(), 1U);

    const Tensor& input = inputs.front();

    EXPECT_EQ(input.Specification().Name(), "images");
    EXPECT_EQ(input.Specification().Type(), TensorType::Float32);
    EXPECT_EQ(input.Specification().Rank(), 4U);
    EXPECT_EQ(input.Specification().Dimension(0), 1);
    EXPECT_EQ(input.Specification().Dimension(1), 3);
    EXPECT_EQ(input.Specification().Dimension(2), 640);
    EXPECT_EQ(input.Specification().Dimension(3), 640);
}

TEST_F(OnnxBackendTest, Output)
{
    ASSERT_TRUE(backend.LoadModel(kModelPath));

    const std::vector<Tensor>& outputs = backend.Outputs();

    ASSERT_EQ(outputs.size(), 1U);

    const Tensor& output = outputs.front();

    EXPECT_EQ(output.Specification().Name(), "output0");
    EXPECT_EQ(output.Specification().Type(), TensorType::Float32);
    EXPECT_EQ(output.Specification().Rank(), 3U);
    EXPECT_EQ(output.Specification().Dimension(0), 1);
    EXPECT_EQ(output.Specification().Dimension(1), 84);
    EXPECT_EQ(output.Specification().Dimension(2), 8400);
}

TEST_F(OnnxBackendTest, Infer)
{
    ASSERT_TRUE(backend.LoadModel(kModelPath));

    EXPECT_TRUE(backend.Infer());
}

TEST_F(OnnxBackendTest, InferWritesOutput)
{
    ASSERT_TRUE(backend.LoadModel(kModelPath));

    Tensor& input = backend.Inputs().front();
    Tensor& output = backend.Outputs().front();

    std::memset(input.Data(), 0, input.ByteSize());
    std::memset(output.Data(), 0, output.ByteSize());

    ASSERT_TRUE(backend.Infer());

    const std::uint8_t* data = static_cast<const std::uint8_t*>(output.Data());

    const bool written = std::any_of(data,
                                     data + output.ByteSize(),
                                    [](std::uint8_t value)
                                    {
                                        return value != 0;
                                    });

    EXPECT_TRUE(written);
}

} // namespace vp
