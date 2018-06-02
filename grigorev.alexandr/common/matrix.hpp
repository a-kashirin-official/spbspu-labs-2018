#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include "shape.hpp"

namespace grigorev
{
  class Matrix
  {
  public:
    Matrix(const std::shared_ptr< grigorev::Shape > shape);
    Matrix(const Matrix & matrix);
    Matrix(Matrix && matrix);
    Matrix & operator = (const Matrix & matrix);
    Matrix & operator = (Matrix && matrix);
    std::unique_ptr< std::shared_ptr< grigorev::Shape >[] > operator[](const int layerIndex) const;
    void addShape(const std::shared_ptr< grigorev::Shape > shape);
  private:
    std::unique_ptr < std::shared_ptr < grigorev::Shape >[] > list_;
    int layersCount_;
    int layerSize_;
    bool checkOverlapping(const int index, std::shared_ptr< grigorev::Shape > shape) const;
  };
}
#endif
