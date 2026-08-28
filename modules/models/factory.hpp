#pragma once

#include <filesystem>
#include <memory>

#include "model.hpp"
#include "descriptor.hpp"
#include "backend.hpp"
#include "profiler_macros.hpp"

namespace vp
{

/**
 * @brief Factory for inference models.
 *
 * Creates inference model instances from a model descriptor.
 */
class ModelFactory
{
public:

    /**
     * @brief Creates an inference model.
     *
     * @param descriptor Model descriptor.
     *
     * @return Created inference model.
     *
     * @throws std::runtime_error If the requested model is not supported.
     */
    static std::unique_ptr<Model> Create(const ModelDescriptor& descriptor);

private:

    static std::filesystem::path ResolveModelPath(const ModelDescriptor& descriptor);

    static std::unique_ptr<Backend> CreateBackend(BackendType backend_type,
                                                  const std::filesystem::path& model_path);

    static std::unique_ptr<Model> CreateModel(ModelType model_type,
                                              std::unique_ptr<Backend> backend);
};

} // namespace vp
