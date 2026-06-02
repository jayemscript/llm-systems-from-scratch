// src/tensor/tensor.hpp
#ifndef TENSOR_HPP
#define TENSOR_HPP

#include <vector>
#include <numeric>
#include <stdexcept>

template <typename T>
class Tensor {
public:
    // constructors
    explicit Tensor(const std::vector<size_t>& shape);
    Tensor(const std::vector<size_t>& shape, const std::vector<T>& data);

    // access
    T at(const std::vector<size_t>& indices) const;
    void set(const std::vector<size_t>& indices, T value);
    T* data();
    const T* data() const;

    // info
    const std::vector<size_t>& shape() const;
    size_t rank() const;
    size_t size() const;

    // utility
    void reshape(const std::vector<size_t>& new_shape);

private:
    std::vector<T>      data_;
    std::vector<size_t> shape_;
    size_t              size_;

    // converts multi-dimensional index to flat array index
    size_t flat_index(const std::vector<size_t>& indices) const;
};
// --- IMPLEMENTATION ---
template <typename T>
Tensor<T>::Tensor(const std::vector<size_t>& shape)
    : shape_(shape)
    , size_(std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<size_t>()))
    , data_(size_, T{})
{}

template <typename T>
Tensor<T>::Tensor(const std::vector<size_t>& shape, const std::vector<T>& data)
    : shape_(shape)
    , size_(std::accumalate(shape.begin(), shape.end(),  1, std::multiplies<size_t>()))
    , data_(data)
    {
        if (data.size() != size_) {
            throw std::invalid_argument("data size does not match shape")
        }
    }

#endif