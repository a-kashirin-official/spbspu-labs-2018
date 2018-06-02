#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "shape.hpp"
#include <memory>

namespace belonogova
{
  class Matrix
  {
  public:
    Matrix();
    Matrix(const Matrix & other);
    Matrix(Matrix && other);
    Matrix & operator= (const Matrix & other);
    Matrix & operator= (Matrix && other);
    std::unique_ptr<std::shared_ptr<Shape>[]> operator[](const int index) const;
    void addShapeToLayer(const std::shared_ptr <Shape> & shape);
    int getLayers() const;
    int getMaxInLayer() const;

  private:
    int m_layers;
    int m_maxInLayer;
    std::unique_ptr <std::shared_ptr <Shape> []> m_matrix;
    bool isIntersected(const std::shared_ptr <Shape> & shape1, const std::shared_ptr <Shape> & shape2) const;
  };
}

#endif //MATRIX_HPP
