#pragma once

#include <memory>
#include <vector>

#include "frame.hpp"
#include "inference_model.hpp"

namespace vp
{

/**
 * @brief Orchestrates the execution of inference models.
 *
 * The engine manages a collection of inference models and executes them for
 * each input frame. It is agnostic to the tasks performed by the models and to
 * the types of outputs they produce.
 */
class Engine
{
public:

    /**
     * @brief Constructs an inference engine.
     */
    Engine() = default;

    /**
     * @brief Destroys the inference engine.
     */
    virtual ~Engine() = default;

    /**
     * @brief Adds an inference model to the engine.
     *
     * @param model Inference model.
     */
    void AddModel(std::shared_ptr<InferenceModel> model);

    /**
     * @brief Removes an inference model from the engine.
     *
     * @param model Inference model.
     */
    void RemoveModel(std::shared_ptr<InferenceModel> model);

    /**
     * @brief Removes all inference models.
     */
    void ClearModels();

    /**
     * @brief Executes all registered inference models.
     *
     * @param frame Input frame.
     */
    void Process(const Frame& frame);

private:

    std::vector<std::shared_ptr<InferenceModel>> models_;
};

} // namespace vp
