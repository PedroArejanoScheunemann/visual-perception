#pragma once

#include <cstddef>
#include <initializer_list>
#include <vector>

namespace vp
{

/**
 * @brief Represents the dimensions of a tensor.
 */
class TensorShape
{
public:

    /**
     * @brief Creates an empty tensor shape.
     */
    TensorShape() = default;

    /**
     * @brief Creates a tensor shape.
     *
     * @param dimensions Tensor dimensions.
     */
    TensorShape(std::initializer_list<std::size_t> dimensions);

    /**
     * @brief Returns the tensor dimensions.
     *
     * @return Tensor dimensions.
     */
    const std::vector<std::size_t>& Get() const;

    /**
     * @brief Returns the tensor rank.
     *
     * @return Number of dimensions.
     */
    std::size_t Rank() const;

    /**
     * @brief Returns the number of tensor elements.
     *
     * @return Number of elements.
     */
    std::size_t Size() const;

    /**
     * @brief Returns a tensor dimension.
     *
     * @param index Dimension index.
     *
     * @return Dimension size.
     */
    std::size_t operator[](std::size_t index) const;

private:

    std::vector<std::size_t> dimensions_;
    std::size_t size_ = 0;
};

} // namespace vp
