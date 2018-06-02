#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <memory>
#include "shape.hpp"
#include "composite-shape.hpp"

namespace shumkovskaya

{
  class Matrix
  {
  public:
    Matrix(const CompositeShape shapes);
    Matrix(const Matrix & rhs);
    Matrix & operator = (const Matrix & rsh);
    std::unique_ptr <std::shared_ptr<Shape>[]>::pointer operator[](int index) const;
    void addShape(const std::shared_ptr<Shape> shape) noexcept;
    void addLayer(std::shared_ptr<Shape> shape);
    bool checkIntersection(std::shared_ptr<Shape> shape, const int index) const noexcept;
    int getAmount();
    int getSize();
  private:
    int amount_;
    int size_;
    std::unique_ptr<std::shared_ptr<Shape>[]> shapes_;
  };
}

#endif
