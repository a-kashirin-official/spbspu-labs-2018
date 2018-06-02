#ifndef STARIKOV_ANDREY_LABS_MATRIX_HPP
#define STARIKOV_ANDREY_LABS_MATRIX_HPP

#include <iostream>
#include <memory>
#include "shape.hpp"

namespace starikov
{
  class Matrix
  {
  public:
    Matrix(const std::shared_ptr<Shape> shape);
    Matrix() noexcept;
    ~Matrix();

    Matrix(const Matrix & matrix);
    Matrix(Matrix && matrix);
    const Shape & operator [](int index) const;
    Matrix & operator=(const Matrix & matrix);
    Matrix & operator=(Matrix && matrix);

    void addShape(const std::shared_ptr<Shape> newShape);
    int getLayerSize() noexcept;
    int getShapeSize() noexcept;
  private:
    int sizeLayer_;
    int sizeShape_;
    std::unique_ptr<std::shared_ptr<Shape>[]> arrayShape_;

    bool crossChecking(const std::shared_ptr<Shape> &shapeCurr, const std::shared_ptr<Shape> &shapeNew) const;

  };
}

#endif //STARIKOV_ANDREY_LABS_MATRIX_HPP
