#include "tensor_shape.hpp"

#include <stdexcept>
#include <utility>

namespace vp
{

TensorShape::TensorShape(std::initializer_list<std::int64_t> dimensions) :
                         dimensions_(dimensions)
{
}

TensorShape::TensorShape(std::vector<std::int64_t> dimensions) :
                         dimensions_(std::move(dimensions))
{
}

const std::vector<std::int64_t>& TensorShape::Get() const
{
    return dimensions_;
}

std::size_t TensorShape::Rank() const
{
    return dimensions_.size();
}

std::size_t TensorShape::Size() const
{
    std::size_t size = 1;

    for (std::int64_t dimension : dimensions_)
    {
        if (dimension < 0)
        {
            throw std::invalid_argument("Tensor size is undefined for dynamic shapes.");
        }

        size *= static_cast<std::size_t>(dimension);
    }

    return size;
}

std::int64_t TensorShape::operator[](std::size_t index) const
{
    return dimensions_[index];
}

} // namespace vp
