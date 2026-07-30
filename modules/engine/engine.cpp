#include "engine.hpp"

#include <algorithm>

#include "factory.hpp"
#include "object_detection_model.hpp"

namespace vp
{

Model& Engine::AddModel(std::unique_ptr<Model> model)
{
    models_.push_back(std::move(model));

    return *models_.back();
}

Model& Engine::AddModel(const ModelDescriptor& descriptor)
{
    std::unique_ptr<Model> model = ModelFactory::Create(descriptor);

    BindModel(*model, descriptor);

    return AddModel(std::move(model));
}


void Engine::BindModel(Model& model, const ModelDescriptor& descriptor)
{
    switch (descriptor.category)
    {
        case DetectionCategory::Object:
            static_cast<ObjectDetectionModel&>(model).Bind(state_.Detections());
            break;
    }
}

void Engine::RemoveModel(Model& model)
{
    models_.erase(std::remove_if(models_.begin(),
                                 models_.end(),
                                 [&model](const std::unique_ptr<Model>& current)
                                 {
                                     return current.get() == &model;
                                 }),
                                models_.end());
}

void Engine::ClearModels()
{
    models_.clear();
    state_.Clear();
}

void Engine::Process(const Frame& frame)
{
    state_.Clear();

    for (const auto& model : models_)
    {
        model->Process(frame);
    }
}

const ObjectDetections& Engine::Detections() const
{
    return state_.Detections();
}

} // namespace vp
