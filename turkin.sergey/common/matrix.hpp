#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "shape.hpp"
#include "composite-shape.hpp"
#include <memory>

namespace turkin
{
  class Matrix
  {
  public:
    explicit Matrix(std::shared_ptr<turkin::Shape> newSh);
    Matrix(const Matrix &matrix);
    Matrix(Matrix &&matrix) noexcept;
    ~Matrix();

    Matrix &operator=(const Matrix &matrix);
    Matrix &operator=(Matrix &&matrix) noexcept;
    std::unique_ptr<std::shared_ptr<turkin::Shape>[]> operator[](size_t layerIndex) const;

    size_t getLayersNumber() const noexcept;
    size_t getLayerSize() const noexcept;
    void addShape(std::shared_ptr<turkin::Shape> newSh);
    void addFromShape(const std::shared_ptr<turkin::CompositeShape> &CShape, size_t size);

  private:
    std::unique_ptr<std::shared_ptr<turkin::Shape>[]> array_;
    size_t layerCount;
    size_t size_;
    bool crossing(size_t index, std::shared_ptr<turkin::Shape> newSh) const noexcept;
  };
}


#endif
