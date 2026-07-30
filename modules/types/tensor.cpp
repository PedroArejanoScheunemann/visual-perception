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

Tensor::Tensor(const TensorSpecification& specification) :
               specification_(specification)
{
    Allocate();
}

const void* Tensor::Data() const
{
    return data_.data();
}

void* Tensor::Data()
{
    return data_.data();
}

std::size_t Tensor::ByteSize() const
{
    return data_.size();
}

const TensorSpecification& Tensor::Specification() const
{
    return specification_;
}

void Tensor::Allocate()
{
    data_.resize(specification_.Size() * kTensorElementSizes[static_cast<std::size_t>(specification_.Type())]);
}

} // namespace vp
