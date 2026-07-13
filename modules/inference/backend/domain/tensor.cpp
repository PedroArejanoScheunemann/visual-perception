#include "tensor.hpp"

namespace
{

constexpr std::size_t kTensorElementSizes[]
{
    sizeof(float),
    sizeof(std::uint16_t),
    sizeof(std::int32_t),
    sizeof(std::int8_t),
    sizeof(std::uint8_t)
};

} // namespace

namespace vp
{

Tensor::Tensor(const TensorSpecification& descriptor) :
               descriptor_(descriptor)
{
    Allocate();
}

void* Tensor::Data()
{
    return data_.data();
}

std::size_t Tensor::Size() const
{
    return data_.size();
}

const TensorSpecification& Tensor::Descriptor() const
{
    return descriptor_;
}

void Tensor::Allocate()
{
    data_.resize(descriptor_.Size() * kTensorElementSizes[static_cast<std::size_t>(descriptor_.Type())]);
}

} // namespace vp
