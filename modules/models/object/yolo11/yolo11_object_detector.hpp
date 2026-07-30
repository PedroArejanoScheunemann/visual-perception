#pragma once

#include <memory>

#include "backend.hpp"
#include "object_detection_model.hpp"
#include "yolo11_decoder.hpp"
#include "yolo11_preprocessor.hpp"

namespace vp
{

/**
 * @brief YOLO11 object detector.
 */
class Yolo11ObjectDetector final : public ObjectDetectionModel
{
public:

    /**
     * @brief Constructs a YOLO11 object detector.
     *
     * @param backend Inference backend.
     */
    explicit Yolo11ObjectDetector(std::unique_ptr<Backend> backend);

    /**
     * @brief Executes the complete YOLO11 inference pipeline.
     *
     * @param frame Input frame.
     */
    void Process(const Frame& frame) override;

protected:

    void OnBind() override;

private:

    std::unique_ptr<Backend> backend_;

    Yolo11Preprocessor preprocessor_;

    Yolo11Decoder decoder_;
};

} // namespace vp
