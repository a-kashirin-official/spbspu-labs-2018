#ifndef MATRIX_SHAPE_HPP
#define MATRIX_SHAPE_HPP

#include "shape.hpp"
#include <memory>

namespace egorov
{
  class MatrixShape
  {
  public:

    MatrixShape();

    MatrixShape(const MatrixShape &object);

    MatrixShape(MatrixShape &&object) noexcept;

    MatrixShape &operator=(const MatrixShape &rhs);

    MatrixShape &operator=(MatrixShape &&rhs) noexcept;

    std::unique_ptr<std::shared_ptr<Shape>[]>::pointer operator[](const size_t index) const;

    void addShape(const std::shared_ptr<Shape> &shape);

    void printInfo() noexcept;

  private:
    size_t rows_, columns_;
    std::unique_ptr<std::shared_ptr<Shape>[]> groups_;
    bool crossing(const std::shared_ptr<Shape> &shape1, const std::shared_ptr<Shape> &shape2) noexcept;
  };
}

#endif
