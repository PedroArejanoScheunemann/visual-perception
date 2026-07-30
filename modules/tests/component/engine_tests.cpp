#include <gtest/gtest.h>

#include "engine.hpp"

namespace vp
{
namespace
{

TEST(EngineTest, AddModel)
{
    Engine engine;

    ModelDescriptor descriptor{
        .category = DetectionCategory::Object,
        .backend = BackendType::Onnx,
        .model = ModelType::Yolo11n
    };

    EXPECT_NO_THROW({
        Model& model = engine.AddModel(descriptor);
        (void)model;
    });
}

TEST(EngineTest, RemoveModel)
{
    Engine engine;

    ModelDescriptor descriptor{
        .category = DetectionCategory::Object,
        .backend = BackendType::Onnx,
        .model = ModelType::Yolo11n
    };

    Model& model = engine.AddModel(descriptor);

    EXPECT_NO_THROW(engine.RemoveModel(model));
}

TEST(EngineTest, ClearModels)
{
    Engine engine;

    ModelDescriptor descriptor{
        .category = DetectionCategory::Object,
        .backend = BackendType::Onnx,
        .model = ModelType::Yolo11n
    };

    engine.AddModel(descriptor);
    engine.AddModel(descriptor);

    EXPECT_NO_THROW(engine.ClearModels());
}

TEST(EngineTest, ProcessWithoutModels)
{
    Engine engine;

    Frame frame;

    EXPECT_NO_THROW(engine.Process(frame));
}

} // namespace
} // namespace vp
