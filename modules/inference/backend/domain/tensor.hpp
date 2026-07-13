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
 * Stores a contiguous memory buffer together with its descriptor.
 */
class Tensor
{
public:

    /**
     * @brief Constructs a tensor.
     *
     * @param descriptor Tensor descriptor.
     */
    explicit Tensor(const TensorSpecification& descriptor);

    /**
     * @brief Returns a pointer to the tensor data.
     *
     * @return Pointer to the tensor data.
     */
    void* Data();

    /**
     * @brief Returns the tensor size in bytes.
     *
     * @return Tensor size in bytes.
     */
    std::size_t Size() const;

    /**
     * @brief Returns the tensor descriptor.
     *
     * @return Tensor descriptor.
     */
    const TensorSpecification& Descriptor() const;

private:

    /**
     * @brief Allocates the tensor memory.
     */
    void Allocate();

private:

    TensorSpecification descriptor_;
    std::vector<std::uint8_t> data_;
};

} // namespace vp
