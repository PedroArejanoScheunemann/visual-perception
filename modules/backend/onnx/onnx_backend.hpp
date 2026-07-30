#pragma once

#include <memory>
#include <onnxruntime_cxx_api.h>
#include <vector>

#include "backend.hpp"

namespace vp
{

/**
 * @brief ONNX Runtime inference backend.
 */
class OnnxBackend : public Backend
{
public:

    /**
     * @brief Constructs an ONNX Runtime backend.
     */
    OnnxBackend();

    /**
     * @brief Loads an ONNX model.
     *
     * @param model_path Path to the model.
     *
     * @return True if the model was loaded successfully, false otherwise.
     */
    bool LoadModel(const std::filesystem::path& model_path) override;

    /**
     * @brief Runs inference.
     *
     * @return True if the inference completed successfully, false otherwise.
     */
    bool Infer() override;

    /**
     * @brief Returns the model input tensors.
     *
     * @return Model input tensors.
     */
    std::vector<Tensor>& Inputs() override;

    /**
     * @brief Returns the model input tensors.
     *
     * @return Model input tensors.
     */
    const std::vector<Tensor>& Inputs() const override;

    /**
     * @brief Returns the model output tensors.
     *
     * @return Model output tensors.
     */
    std::vector<Tensor>& Outputs() override;

    /**
     * @brief Returns the model output tensors.
     *
     * @return Model output tensors.
     */
    const std::vector<Tensor>& Outputs() const override;

private:

    /**
     * @brief Loads the model input tensors.
     */
    void LoadInputs();

    /**
     * @brief Loads the model output tensors.
     */
    void LoadOutputs();

    /**
     * @brief Converts an ONNX tensor shape.
     *
     * @param tensor_info ONNX tensor information.
     *
     * @return Tensor shape.
     */
    TensorShape ConvertShape(const Ort::ConstTensorTypeAndShapeInfo& tensor_info) const;

    /**
     * @brief Converts an ONNX tensor type.
     *
     * @param tensor_info ONNX tensor information.
     *
     * @return Tensor type.
     */
    TensorType ConvertType(const Ort::ConstTensorTypeAndShapeInfo& tensor_info) const;

    /**
     * @brief Converts a tensor type to an ONNX tensor type.
     *
     * @param type Tensor type.
     *
     * @return ONNX tensor type.
     */
    ONNXTensorElementDataType ConvertType(TensorType type) const;

private:

    Ort::Env environment_;
    Ort::SessionOptions session_options_;
    Ort::MemoryInfo memory_info_;
    std::unique_ptr<Ort::Session> session_;

    std::vector<Tensor> input_tensors_;
    std::vector<Tensor> output_tensors_;

    std::vector<const char*> input_names_;
    std::vector<const char*> output_names_;

    std::vector<Ort::Value> input_values_;
    std::vector<Ort::Value> output_values_;
};

} // namespace vp
