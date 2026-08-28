#include "factory.hpp"

#include <stdexcept>

#include "onnx_backend.hpp"
#include "yolo11_object_detector.hpp"

namespace vp
{
std::unique_ptr<Model> ModelFactory::Create(const ModelDescriptor& descriptor)
{
    const std::filesystem::path model_path = ResolveModelPath(descriptor);

    std::unique_ptr<Backend> backend = CreateBackend(descriptor.backend, model_path);

    return CreateModel(descriptor.model, std::move(backend));
}

std::filesystem::path ModelFactory::ResolveModelPath(const ModelDescriptor& descriptor)
{
    std::filesystem::path path = VP_ASSETS_DIR;

    path /= "weights";
    path /= ModelDescriptor::CategoryName(descriptor.category);
    path /= ModelDescriptor::ModelName(descriptor.model);
    path += '.';
    path += ModelDescriptor::BackendExtension(descriptor.backend);

    if (!std::filesystem::exists(path))
    {
        throw std::runtime_error("Inference model not found: " + path.string());
    }

    return path;
}


std::unique_ptr<Backend> ModelFactory::CreateBackend(BackendType backend_type, const std::filesystem::path& model_path)
{
    std::unique_ptr<Backend> backend;

    switch (backend_type)
    {
    case BackendType::Onnx:
        backend = std::make_unique<OnnxBackend>();
        break;

    case BackendType::CoreML:
        throw std::runtime_error("CoreML backend is not implemented.");
    }

    if (!backend->LoadModel(model_path))
    {
        throw std::runtime_error("Failed to load inference model: " + model_path.string());
    }

    return backend;
}

std::unique_ptr<Model> ModelFactory::CreateModel(ModelType model_type, std::unique_ptr<Backend> backend)
{
    switch (model_type)
    {
    case ModelType::Yolo11n:
    case ModelType::Yolo11s:
    case ModelType::Yolo11m:
    case ModelType::Yolo11l:
    case ModelType::Yolo11x:
        return std::make_unique<Yolo11ObjectDetector>(std::move(backend));
    }

    throw std::runtime_error("Unsupported inference model.");
}

} // namespace vp
