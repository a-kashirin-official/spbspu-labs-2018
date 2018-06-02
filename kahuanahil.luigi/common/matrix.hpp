#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "shape.hpp"
#include <memory>

namespace kahuanahil
{
  class Matrix
  {
  public:
    Matrix(const std::shared_ptr<kahuanahil::Shape> shape);
    Matrix(const Matrix &matrix);
    Matrix(Matrix &&matrix);
    ~Matrix();
    Matrix &operator=(const Matrix &matrix);
    Matrix &operator=(Matrix &&matrix);
    bool operator==(const Matrix &matrix) const;
    bool operator!=(const Matrix &matrix) const;
    std::unique_ptr<std::shared_ptr<kahuanahil::Shape>[]> operator[](const int Lnumber) const;
    void addShape(const std::shared_ptr<kahuanahil::Shape> shape);

  private:
    std::unique_ptr<std::shared_ptr<kahuanahil::Shape>[]> matrixShape;
    int Lnumber_;
    int Lsize_;
    bool Checkforoverlap(const int index, std::shared_ptr<kahuanahil::Shape> shape) const noexcept;
  };
} 

#endif
