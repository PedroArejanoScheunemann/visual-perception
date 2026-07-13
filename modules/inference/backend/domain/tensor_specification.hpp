#pragma once

#include <cstddef>
#include <cstdint>

#include "tensor_shape.hpp"
#include "tensor_type.hpp"

namespace vp
{

/**
 * @brief Tensor memory layout.
 */
enum class TensorLayout : std::uint8_t
{
    /**
     * @brief Batch, Channels, Height, Width.
     */
    NCHW = 0,

    /**
     * @brief Batch, Height, Width, Channels.
     */
    NHWC
};

/**
 * @brief Describes a tensor.
 */
class TensorSpecification
{
public:

    /**
     * @brief Constructs a tensor specification.
     *
     * @param shape Tensor shape.
     * @param type Tensor element type.
     * @param layout Tensor layout.
     */
    TensorSpecification(TensorShape shape, TensorType type, TensorLayout layout = TensorLayout::NCHW);

    /**
     * @brief Returns the tensor shape.
     *
     * @return Tensor shape.
     */
    const TensorShape& Shape() const;

    /**
     * @brief Returns the tensor element type.
     *
     * @return Tensor element type.
     */
    TensorType Type() const;

    /**
     * @brief Returns the tensor layout.
     *
     * @return Tensor layout.
     */
    TensorLayout Layout() const;

    /**
     * @brief Returns the tensor rank.
     *
     * @return Tensor rank.
     */
    std::size_t Rank() const;

    /**
     * @brief Returns the number of tensor elements.
     *
     * @return Number of tensor elements.
     */
    std::size_t Size() const;

    /**
     * @brief Returns the batch size.
     *
     * @return Batch size.
     */
    std::size_t BatchSize() const;

    /**
     * @brief Returns the number of channels.
     *
     * @return Number of channels.
     */
    std::size_t Channels() const;

    /**
     * @brief Returns the tensor height.
     *
     * @return Tensor height.
     */
    std::size_t Height() const;

    /**
     * @brief Returns the tensor width.
     *
     * @return Tensor width.
     */
    std::size_t Width() const;

    /**
    * @brief Returns the size of a tensor dimension.
    *
    * @param index Dimension index.
    *
    * @return Dimension size.
    */
    std::size_t Dimension(std::size_t index) const;

private:

    TensorShape shape_;
    TensorType type_;
    TensorLayout layout_;
};

} // namespace vp
