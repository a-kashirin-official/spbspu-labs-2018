#ifndef MATRIX_HPP
#define MATRIX_CPP

#include "shape.hpp"
#include <iostream>
#include <memory>

namespace gessen
{
  class Matrix
  {
    public:
      Matrix();
      Matrix(Shape *shp);
      Matrix(const Matrix &mtrx);
      Matrix(Matrix &&mtrx);
      ~Matrix();
      Matrix &operator=(Matrix &mtrx);
      Matrix &operator=(Matrix &&mtrx);
      Shape *operator[](int num) const;
      void addShape(Shape *shp);
      int getNum() const;
      void printShapes();
    private:
      std::unique_ptr<Shape*[]> matrixList_;
      int shapeCounter_;
      bool overlapping(const Shape *shp1, const Shape *shp2);
  };
}

#endif

