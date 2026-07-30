#include "onnx_backend.hpp"

namespace vp
{

OnnxBackend::OnnxBackend() :
                         environment_(ORT_LOGGING_LEVEL_WARNING, "vp"),
                         memory_info_(Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault))
{
    session_options_.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_ALL);
}

bool OnnxBackend::LoadModel(const std::filesystem::path& model_path)
{
    try
    {
        session_ = std::make_unique<Ort::Session>(environment_,model_path.c_str(), session_options_);

        LoadInputs();
        LoadOutputs();

        return true;
    }
    catch (const Ort::Exception&)
    {
        session_.reset();

        input_tensors_.clear();
        output_tensors_.clear();

        input_names_.clear();
        output_names_.clear();

        input_values_.clear();
        output_values_.clear();

        return false;
    }
}

bool OnnxBackend::Infer()
{
    if (!session_)
    {
        return false;
    }

    try
    {
        session_->Run(Ort::RunOptions{nullptr},
                      input_names_.data(),
                      input_values_.data(),
                      input_values_.size(),
                      output_names_.data(),
                      output_values_.data(),
                      output_values_.size());

        return true;
    }
    catch (const Ort::Exception&)
    {
        return false;
    }
}

std::vector<Tensor>& OnnxBackend::Inputs()
{
    return input_tensors_;
}

const std::vector<Tensor>& OnnxBackend::Inputs() const
{
    return input_tensors_;
}

std::vector<Tensor>& OnnxBackend::Outputs()
{
    return output_tensors_;
}

const std::vector<Tensor>& OnnxBackend::Outputs() const
{
    return output_tensors_;
}

void OnnxBackend::LoadInputs()
{
    input_tensors_.clear();
    input_names_.clear();
    input_values_.clear();

    Ort::AllocatorWithDefaultOptions allocator;

    const std::size_t count = session_->GetInputCount();

    input_tensors_.reserve(count);
    input_names_.reserve(count);
    input_values_.reserve(count);

    for (std::size_t i = 0; i < count; ++i)
    {
        const auto name = session_->GetInputNameAllocated(i, allocator);
        const auto type_info = session_->GetInputTypeInfo(i);
        const auto tensor_info = type_info.GetTensorTypeAndShapeInfo();

        input_tensors_.emplace_back(TensorSpecification(name.get(),
                                                        ConvertShape(tensor_info),
                                                        ConvertType(tensor_info)));

        Tensor& tensor = input_tensors_.back();
        const TensorSpecification& specification = tensor.Specification();

        input_names_.push_back(specification.Name().c_str());
        input_values_.emplace_back(Ort::Value::CreateTensor(memory_info_,
                                                            tensor.Data(),
                                                            tensor.ByteSize(),
                                                            specification.Shape().Get().data(),
                                                            specification.Rank(),
                                                            ConvertType(specification.Type())));
    }
}

void OnnxBackend::LoadOutputs()
{
    output_tensors_.clear();
    output_names_.clear();
    output_values_.clear();

    Ort::AllocatorWithDefaultOptions allocator;

    const std::size_t count = session_->GetOutputCount();

    output_tensors_.reserve(count);
    output_names_.reserve(count);
    output_values_.reserve(count);

    for (std::size_t i = 0; i < count; ++i)
    {
        const auto name = session_->GetOutputNameAllocated(i, allocator);
        const auto type_info = session_->GetOutputTypeInfo(i);
        const auto tensor_info = type_info.GetTensorTypeAndShapeInfo();

        output_tensors_.emplace_back(TensorSpecification(name.get(),
                                                         ConvertShape(tensor_info),
                                                         ConvertType(tensor_info)));

        Tensor& tensor = output_tensors_.back();
        const TensorSpecification& specification = tensor.Specification();

        output_names_.push_back( tensor.Specification().Name().c_str());
        output_values_.emplace_back(Ort::Value::CreateTensor(memory_info_,
                                                             tensor.Data(),
                                                             tensor.ByteSize(),
                                                             specification.Shape().Get().data(),
                                                             specification.Rank(),
                                                             ConvertType(specification.Type())));
    }
}

TensorShape OnnxBackend::ConvertShape(const Ort::ConstTensorTypeAndShapeInfo& tensor_info) const
{
    return TensorShape(tensor_info.GetShape());
}

TensorType OnnxBackend::ConvertType(const Ort::ConstTensorTypeAndShapeInfo& tensor_info) const
{
    switch (tensor_info.GetElementType())
    {
        case ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT:
            return TensorType::Float32;

        case ONNX_TENSOR_ELEMENT_DATA_TYPE_INT32:
            return TensorType::Int32;

        case ONNX_TENSOR_ELEMENT_DATA_TYPE_INT8:
            return TensorType::Int8;

        case ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT8:
            return TensorType::UInt8;

        default:
            throw std::runtime_error("Unsupported tensor element type.");
    }
}

ONNXTensorElementDataType OnnxBackend::ConvertType(TensorType type) const
{
    switch (type)
    {
        case TensorType::Float32:
            return ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT;

        case TensorType::Int32:
            return ONNX_TENSOR_ELEMENT_DATA_TYPE_INT32;

        case TensorType::Int8:
            return ONNX_TENSOR_ELEMENT_DATA_TYPE_INT8;

        case TensorType::UInt8:
            return ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT8;

        default:
            throw std::runtime_error("Unsupported tensor type.");
    }
}

} // namespace vp
