#include <gtest/gtest.h>

#include "factory.hpp"

namespace vp
{
namespace
{

TEST(ModelFactoryTest, CreateValidModel)
{
    ModelDescriptor descriptor{
        .category = DetectionCategory::Object,
        .backend = BackendType::Onnx,
        .model = ModelType::Yolo11n
    };

    ASSERT_NE(ModelFactory::Create(descriptor), nullptr);
}

TEST(ModelFactoryTest, MissingCategoryThrows)
{
    ModelDescriptor descriptor{
        .category = DetectionCategory::Face,
        .backend = BackendType::Onnx,
        .model = ModelType::Yolo11n
    };

    EXPECT_THROW(ModelFactory::Create(descriptor), std::runtime_error);
}

TEST(ModelFactoryTest, MissingBackendThrows)
{
    ModelDescriptor descriptor{
        .category = DetectionCategory::Object,
        .backend = BackendType::CoreML,
        .model = ModelType::Yolo11n
    };

    EXPECT_THROW(ModelFactory::Create(descriptor), std::runtime_error);
}

TEST(ModelFactoryTest, MissingModelThrows)
{
    ModelDescriptor descriptor{
        .category = DetectionCategory::Object,
        .backend = BackendType::Onnx,
        .model = ModelType::Yolo11x
    };

    EXPECT_THROW(ModelFactory::Create(descriptor), std::runtime_error);
}

} // namespace
} // namespace vp
