#include "tensor_specification.hpp"

#include <cassert>

namespace vp
{

TensorSpecification::TensorSpecification(std::string name, TensorShape shape, TensorType type) :
                                         name_(std::move(name)),
                                         shape_(std::move(shape)),
                                         type_(type)
{
}

const TensorShape& TensorSpecification::Shape() const
{
    return shape_;
}

const std::string& TensorSpecification::Name() const
{
    return name_;
}

TensorType TensorSpecification::Type() const
{
    return type_;
}

std::size_t TensorSpecification::Rank() const
{
    return shape_.Rank();
}

std::size_t TensorSpecification::Size() const
{
    return shape_.Size();
}

std::size_t TensorSpecification::Dimension(std::size_t index) const
{
    return shape_[index];
}

} // namespace vp
