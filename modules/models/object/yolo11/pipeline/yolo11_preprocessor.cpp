#include "yolo11_preprocessor.hpp"

namespace vp
{

Yolo11Preprocessor::Yolo11Preprocessor(std::vector<Tensor>& inputs) :
                                       inputs_(inputs)
{
}

void Yolo11Preprocessor::Process(const Frame& frame) const
{
    (void)frame;

    // TODO
    //
    // 1. Resize image.
    // 2. Apply letterbox.
    // 3. Convert to RGB.
    // 4. Normalize pixels.
    // 5. Convert HWC -> CHW.
    // 6. Store result into tensor.
}

} // namespace vp
