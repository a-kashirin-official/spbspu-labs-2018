#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include "shape.hpp"
#include "composite-shape.hpp"

namespace semakina
{
  class Matrix
  {
  public:
    Matrix(const std::shared_ptr <Shape> shape);
    Matrix(const semakina::Matrix & matrix);
    Matrix(const semakina::CompositeShape & compositeshape);
    ~Matrix();
    Matrix & operator = (const semakina::Matrix & matrix);
    std::unique_ptr <std::shared_ptr <semakina::Shape>[] >::pointer operator[](const int index) const;
    void addShape(const std::shared_ptr <semakina::Shape> shape);
    int getLine() const noexcept;
    int getColumn() const noexcept;
  private:
    int line_;
    int column_;
    std::unique_ptr <std::shared_ptr <semakina::Shape>[] > matrix_;
    bool checkLayer(const int index, const std::shared_ptr <semakina::Shape> shape) const noexcept;
  };
}

#endif // MATRIX_HPP
