#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "shape.hpp"
#include "composite-shape.hpp"
#include <memory>

namespace tseptsov
{
  class Matrix
  {
  public:
    explicit Matrix(std::shared_ptr < tseptsov::Shape > newSh);
    Matrix(const Matrix &matrix);
    Matrix(Matrix &&matrix) noexcept;
    ~Matrix();

    Matrix &operator=(const Matrix &matrix);
    Matrix &operator=(Matrix &&matrix) noexcept;
    std::unique_ptr < std::shared_ptr < tseptsov::Shape >[] > operator[](size_t layerIndex) const;

    size_t getLayersNumber() const noexcept;
    size_t getLayerSize() const noexcept;
    void addShape(std::shared_ptr < tseptsov::Shape > newSh);
    void addFromCShape(const std::shared_ptr < tseptsov::CompositeShape > &CShape, size_t size);
  private:
    std::unique_ptr < std::shared_ptr < tseptsov::Shape >[] > list_;
    size_t nmbofLayer;
    size_t sizeofLayer;
    bool intersection(const size_t index, std::shared_ptr < tseptsov::Shape > newSh) const noexcept;
  };
}

#endif
