#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "shape.hpp"
#include "composite-shape.hpp"
#include <memory>

namespace khodyreva
{
  class Matrix
  {
  public:
    Matrix(const std::shared_ptr<Shape> & shape);
    Matrix(const Matrix & matrix);
    Matrix(Matrix && matrix);
    Matrix & operator=(const Matrix & matrix);
    Matrix & operator=(Matrix && matrix);
    std::unique_ptr <std::shared_ptr<Shape>[]>:: pointer operator[](const size_t index) const;
    void addShape(const std::shared_ptr<Shape> &);
    size_t getColumns() const;
    size_t getRows() const;
    size_t getLayerSize(const size_t row ) const;
    void addFromCShape(const CompositeShape & composite);
    void printInfo();
  private:
    std::unique_ptr <std::shared_ptr<Shape>[]> data_;
    size_t rows_, columns_;
    bool checkOverlap(const std::shared_ptr<Shape> & shape_1, const std::shared_ptr<Shape> & shape_2) const;
  };

};

#endif // MATRIX_HPP
