#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>

#include "shape.hpp"
#include "composite-shape.hpp"

namespace styagov
{
  class Matrix
  {
  public:
    Matrix() noexcept;
    Matrix(const std::shared_ptr <styagov::Shape> shape);
    Matrix(const styagov::CompositeShape & compositeShape);
    Matrix(const styagov::Matrix & object);
    Matrix(styagov::Matrix && object) noexcept;
    ~Matrix();
    styagov::Matrix & operator=(const styagov::Matrix & object) noexcept;
    styagov::Matrix & operator=(styagov::Matrix && object) noexcept;
    bool operator==(const styagov::Matrix & object) const;
    bool operator!=(const styagov::Matrix & object) const;
    std::unique_ptr <std::shared_ptr <styagov::Shape>[]> operator[] (size_t index) const;
    size_t getLayers() const noexcept;
    size_t getLayerSize() const noexcept;
    size_t getElementsInLayer(size_t index) const;

    void add(const std::shared_ptr <styagov::Shape> shape);
    void clear() noexcept;
    bool doesOverlap(const size_t index, std::shared_ptr <styagov::Shape> shape) const noexcept;

  private:
    std::unique_ptr <std::shared_ptr <styagov::Shape>[]> shapes_;
    size_t layersCount_;
    size_t layerLength_;
  };
}

#endif // MATRIX_HPP
