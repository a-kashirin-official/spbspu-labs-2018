#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "shape.hpp"
#include <memory>

namespace petrachenko
{
  class Matrix
  {
  public:
    Matrix(Shape *shp);
    Matrix(const Matrix &mtrx);
    Matrix(Matrix &&mtrx);
    ~Matrix();
    Matrix &operator=(Matrix &mtrx);
    Matrix &operator=(Matrix &&mtrx);
    Shape *operator[](size_t num) const;
    void addShape(Shape *shp);
    size_t getNum() const;
    void print() ;
  private:
    std::unique_ptr<Shape*[]> elements_;
    size_t numOfShapes_;
    bool isOverlapped(const Shape *shp1, const Shape *shp2);
  };
}

#endif

