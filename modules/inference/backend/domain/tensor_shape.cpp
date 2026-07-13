#include "tensor_shape.hpp"

namespace vp
{

TensorShape::TensorShape(std::initializer_list<std::size_t> dimensions) :
                        dimensions_(dimensions),
                        size_(1)
{
    for (std::size_t dimension : dimensions_)
    {
        size_ *= dimension;
    }
}

const std::vector<std::size_t>& TensorShape::Get() const
{
    return dimensions_;
}

std::size_t TensorShape::Rank() const
{
    return dimensions_.size();
}

std::size_t TensorShape::Size() const
{
    return size_;
}

std::size_t TensorShape::operator[](std::size_t index) const
{
    return dimensions_[index];
}

} // namespace vp
