#include "tensor_specification.hpp"

#include <cassert>

namespace vp
{

TensorSpecification::TensorSpecification(TensorShape shape, TensorType type, TensorLayout layout) :
                                         shape_(std::move(shape)),
                                         type_(type),
                                         layout_(layout)
{
}

const TensorShape& TensorSpecification::Shape() const
{
    return shape_;
}

TensorType TensorSpecification::Type() const
{
    return type_;
}

TensorLayout TensorSpecification::Layout() const
{
    return layout_;
}

std::size_t TensorSpecification::Rank() const
{
    return shape_.Rank();
}

std::size_t TensorSpecification::Size() const
{
    return shape_.Size();
}

std::size_t TensorSpecification::BatchSize() const
{
    return shape_[0];
}

std::size_t TensorSpecification::Channels() const
{
    switch (layout_)
    {
    case TensorLayout::NCHW:
        return shape_[1];

    case TensorLayout::NHWC:
        return shape_[3];
    }

    assert(false);
    return 0U;
}

std::size_t TensorSpecification::Height() const
{
    switch (layout_)
    {
    case TensorLayout::NCHW:
        return shape_[2];

    case TensorLayout::NHWC:
        return shape_[1];
    }

    assert(false);
    return 0U;
}

std::size_t TensorSpecification::Width() const
{
    switch (layout_)
    {
    case TensorLayout::NCHW:
        return shape_[3];

    case TensorLayout::NHWC:
        return shape_[2];
    }

    assert(false);
    return 0U;
}

std::size_t TensorSpecification::Dimension(std::size_t index) const
{
    return shape_[index];
}

} // namespace vp
