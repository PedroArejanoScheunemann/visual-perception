#pragma once

#include <cstddef>
#include <filesystem>

#include "tensor.hpp"

namespace vp
{

/**
 * @brief Interface for inference backends.
 */
class Backend
{
public:

    /**
     * @brief Virtual destructor.
     */
    virtual ~Backend() = default;

    /**
     * @brief Loads an inference model.
     *
     * @param model_path Path to the model.
     *
     * @return True if the model was loaded successfully, false otherwise.
     */
    virtual bool LoadModel(const std::filesystem::path& model_path) = 0;

    /**
     * @brief Runs inference.
     *
     * @return True if the inference completed successfully, false otherwise.
     */
    virtual bool Infer() = 0;

    /**
     * @brief Returns the model input tensors.
     *
     * @return Input tensors.
     */
    virtual std::vector<Tensor>& Inputs() = 0;

    /**
     * @brief Returns the model input tensors.
     *
     * @return Input tensors.
     */
    virtual const std::vector<Tensor>& Inputs() const = 0;

    /**
     * @brief Returns the model output tensors.
     *
     * @return Output tensors.
     */
    virtual std::vector<Tensor>& Outputs() = 0;

    /**
     * @brief Returns the model output tensors.
     *
     * @return Output tensors.
     */
    virtual const std::vector<Tensor>& Outputs() const = 0;
};

} // namespace vp
