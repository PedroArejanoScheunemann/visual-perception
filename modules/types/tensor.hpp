#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include "tensor_specification.hpp"

namespace vp
{

/**
 * @brief Tensor data container.
 *
 * Stores a contiguous memory buffer together with its specification.
 */
class Tensor
{
public:

    /**
     * @brief Constructs a tensor.
     *
     * @param specification Tensor specification.
     */
    explicit Tensor(const TensorSpecification& specification);

    /**
     * @brief Returns a read-only pointer to the tensor data.
     *
     * @return Pointer to the tensor data.
     */
    const void* Data() const;

    /**
     * @brief Returns the tensor data.
     *
     * @return Tensor data.
     */
    void* Data();

    /**
     * @brief Returns the tensor size in bytes.
     *
     * @return Tensor size in bytes.
     */
    std::size_t ByteSize() const;

    /**
     * @brief Returns the tensor specification.
     *
     * @return Tensor specification.
     */
    const TensorSpecification& Specification() const;

private:

    /**
     * @brief Allocates the tensor memory.
     */
    void Allocate();

private:

    TensorSpecification specification_;
    std::vector<std::uint8_t> data_;
};

} // namespace vp
