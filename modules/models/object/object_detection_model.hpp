#pragma once

#include <cassert>

#include "model.hpp"
#include "object_detections.hpp"

namespace vp
{

/**
 * @brief Base class for object detection models.
 *
 * Provides the common infrastructure required by object detection models,
 * including binding the destination where detections are stored.
 */
class ObjectDetectionModel : public Model
{
public:

    /**
     * @brief Binds the destination for detected objects.
     *
     * This method is called by the engine after the model is created. Derived
     * classes may override OnBind() to propagate the binding to their internal
     * components.
     *
     * @param detections Destination where detected objects are stored.
     */
    void Bind(ObjectDetections& detections);

protected:

    /**
     * @brief Called after the object detections are bound.
     *
     * Derived classes may override this method to bind the same destination to
     * internal components.
     */
    virtual void OnBind();

    /**
     * @brief Returns the bound object detections.
     *
     * @return Object detections.
     */
    ObjectDetections& Detections();

    /**
     * @brief Returns the bound object detections.
     *
     * @return Object detections.
     */
    const ObjectDetections& Detections() const;

private:

    ObjectDetections* detections_ = nullptr;
};

} // namespace vp
