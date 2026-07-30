#pragma once

#include <memory>
#include <vector>

#include "frame.hpp"
#include "model.hpp"
#include "descriptor.hpp"
#include "object_detections.hpp"
#include "perception_state.hpp"

namespace vp
{

/**
 * @brief Orchestrates inference models.
 *
 * The engine owns all inference models, executes them for each input frame,
 * and exposes the current perception results.
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
    ~Engine() = default;

    /**
     * @brief Creates and adds an inference model.
     *
     * @param descriptor Model descriptor.
     *
     * @return Reference to the created model.
     */
    Model& AddModel(const ModelDescriptor& descriptor);

    /**
     * @brief Removes a model.
     *
     * @param model Model to remove.
     */
    void RemoveModel(Model& model);

    /**
     * @brief Removes all registered models.
     */
    void ClearModels();

    /**
     * @brief Executes all registered models.
     *
     * @param frame Input frame.
     */
    void Process(const Frame& frame);

    /**
     * @brief Returns the detected objects.
     *
     * @return Object detections.
     */
    const ObjectDetections& Detections() const;

private:

    Model& AddModel(std::unique_ptr<Model> model);
    void BindModel(Model& model, const ModelDescriptor& descriptor);

private:

    std::vector<std::unique_ptr<Model>> models_;

    PerceptionState state_;
};

} // namespace vp
