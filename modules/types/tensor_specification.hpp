#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

#include "tensor_shape.hpp"
#include "tensor_type.hpp"

namespace vp
{

/**
 * @brief Describes a tensor.
 */
class TensorSpecification
{
public:

    /**
     * @brief Constructs a tensor specification.
     *
     * @param name Tensor name.
     * @param shape Tensor shape.
     * @param type Tensor element type.
     */
    TensorSpecification(std::string name, TensorShape shape, TensorType type);

    /**
     * @brief Returns the tensor shape.
     *
     * @return Tensor shape.
     */
    const TensorShape& Shape() const;

    /**
     * @brief Returns the tensor name.
     *
     * @return Tensor name.
     */
    const std::string& Name() const;

    /**
     * @brief Returns the tensor element type.
     *
     * @return Tensor element type.
     */
    TensorType Type() const;

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
    * @brief Returns the size of a tensor dimension.
    *
    * @param index Dimension index.
    *
    * @return Dimension size.
    */
    std::size_t Dimension(std::size_t index) const;

private:

    std::string name_;
    TensorShape shape_;
    TensorType type_;
};

} // namespace vp
