#pragma once

#include "../inference_model.hpp"

#include "domain/person_detections.hpp"

#include "pipeline/yolo11_decoder.hpp"
#include "pipeline/yolo11_preprocessor.hpp"
#include "pipeline/yolo11_model_specification.hpp"

namespace vp
{

/**
 * @brief Detects people using a YOLO11 model.
 *
 * This class implements the complete inference pipeline required to transform
 * an input frame into a collection of person detections.
 */
class Yolo11PersonDetector final : public InferenceModel
{
public:

    /**
     * @brief Constructs a YOLO11 person detector.
     */
    Yolo11PersonDetector();

    /**
     * @brief Executes the complete inference pipeline.
     *
     * @param frame Input frame.
     */
    void Process(const Frame& frame) override;

    /**
     * @brief Returns the latest person detections.
     *
     * @return Person detections.
     */
    const PersonDetections& Detections() const;

private:

    const Yolo11ModelSpecification& specification_;
    Tensor input_;
    Tensor output_;
    Yolo11Preprocessor preprocessor_;
    Yolo11Decoder decoder_;
    PersonDetections detections_;
};

} // namespace vp
