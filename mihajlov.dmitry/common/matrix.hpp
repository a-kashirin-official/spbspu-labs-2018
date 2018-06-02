#ifndef A4_MATRIX_HPP
#define A4_MATRIX_HPP

#include <memory>
#include "composite-shape.hpp"

namespace mihajlov
{
  class Matrix
  {
  public:
    Matrix();
    Matrix(const Matrix& matrix);
    Matrix(Matrix&& matrix);
    ~Matrix() = default;
    Matrix& operator=(const Matrix& matrix);
    Matrix& operator=(Matrix&& matrix);
    std::unique_ptr<std::shared_ptr<Shape>[]> operator[](const int index);
    void addShape(const std::shared_ptr<Shape> shape);
    int getLayersCount() const;
    int getLayerSize() const;
    void view() const;

  private:
    std::unique_ptr<std::shared_ptr<Shape>[]> parts_;
    int layerCount_;
    int layerSize_;
    inline bool controlCross(const std::shared_ptr<Shape> shape1, const std::shared_ptr<Shape> shape2);
  };
}

#endif
