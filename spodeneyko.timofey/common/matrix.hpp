#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include "shape.hpp"

namespace spodeneyko
{
  class MatrixShape
  {
  public:
    MatrixShape(const std::shared_ptr<Shape> & shapeElement);
    MatrixShape(const MatrixShape & object);
    MatrixShape(MatrixShape && object);
    MatrixShape & operator =(const MatrixShape & object);
    MatrixShape & operator =(MatrixShape && object);
    std::unique_ptr<std::shared_ptr<Shape>[]>::pointer operator [](const size_t index);
    void addShape(const std::shared_ptr<Shape> & shapeElement);
    void print() const;

  private:
    using matrix_type = std::unique_ptr<std::shared_ptr<Shape>[]>;
    matrix_type matrix_;
    size_t rows_, columns_;
    bool checkOverlap(const std::shared_ptr<Shape> & shape1, const std::shared_ptr<Shape> & shape2) const;
  };
}

#endif
