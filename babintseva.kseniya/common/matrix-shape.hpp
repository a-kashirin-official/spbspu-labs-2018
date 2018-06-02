#ifndef MATRIX_SHAPE_HPP
#define MATRIX_SHAPE_HPP
#include "shape.hpp"
#include <memory>

namespace babintseva
{
  class MatrixShape
  {
  public:
    MatrixShape(const std::shared_ptr <Shape> &shape);
    MatrixShape(const MatrixShape & shape);
    MatrixShape & operator=(const MatrixShape &shape);
    std::unique_ptr <std::shared_ptr<Shape>[]>::pointer operator[](size_t index) const;
    void addShape(const std::shared_ptr <Shape> &shape);
    void print() const;

  private:
    std::unique_ptr <std::shared_ptr <Shape>[]> matrix_;
    size_t rows_, columns_;
    bool checkIntersection(const std::shared_ptr <Shape> &shape1, const std::shared_ptr <Shape> &shape2);
  };
}

#endif
