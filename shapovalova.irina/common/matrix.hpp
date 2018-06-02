#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "shape.hpp"
#include <memory>

namespace shapovalova
{
  class Matrix
  {
  public:
    Matrix(const std::shared_ptr<Shape> & element);
    Matrix(const Matrix & elem);
    Matrix(Matrix && elem);
    Matrix & operator=(const Matrix & elem);
    Matrix & operator=(Matrix && elem);
    std::unique_ptr<std::shared_ptr<Shape>[]> operator [](const int index) const;

    void addShape(const std::shared_ptr<Shape> & element);
    void print() const noexcept;
    int getRows() const noexcept;
    int getColumns() const noexcept;

  private:
    std::unique_ptr<std::shared_ptr<Shape>[]> matrix_;
    int rows_;
    int columns_;
    bool checkInsertion(const std::shared_ptr<Shape> & shape1, const std::shared_ptr<Shape> & shape2);
  };
}

#endif // MATRIX_HPP

