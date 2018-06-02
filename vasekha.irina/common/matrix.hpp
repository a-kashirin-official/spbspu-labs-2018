#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include "shape.hpp"

namespace vasekha
{
  class Matrix
  {
  public:
    Matrix() noexcept;
    Matrix(const Matrix & matrix);
    Matrix(Matrix && matrix) noexcept;
    Matrix & operator=(const Matrix & matrix);
    Matrix & operator=(Matrix && matrix) noexcept;
    std::unique_ptr<Shape::ptr_shape[]> operator[](size_t index) const;
    void add(const Shape::ptr_shape & shape);
    size_t getCols() const noexcept;
    size_t getRows() const noexcept;
  private:
    std::unique_ptr<Shape::ptr_shape[]> elements_;
    size_t cols_;
    size_t rows_;
    bool checkOverlapping(const size_t index, Shape::ptr_shape shape) const noexcept;
  };
}

#endif
