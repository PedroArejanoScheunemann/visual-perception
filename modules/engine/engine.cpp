#include "engine.hpp"

#include <algorithm>

namespace vp
{

void Engine::AddModel(std::shared_ptr<InferenceModel> model)
{
    if (model == nullptr)
    {
        return;
    }

    models_.push_back(std::move(model));
}

void Engine::RemoveModel(std::shared_ptr<InferenceModel> model)
{
    models_.erase(std::remove(models_.begin(), models_.end(), model),
                  models_.end());
}

void Engine::ClearModels()
{
    models_.clear();
}

void Engine::Process(const Frame& frame)
{
    for (const auto& model : models_)
    {
        model->Process(frame);
    }
}

} // namespace vp
