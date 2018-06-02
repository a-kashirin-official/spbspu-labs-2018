#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "shape.hpp"
#include <memory>

namespace dumaev
{
  class Matrix
  {
  public:
    Matrix(const std::shared_ptr < Shape > shape);
    Matrix(const Matrix & matrix);
    Matrix(Matrix && matrix);
    Matrix &operator=(const Matrix & matrix);
    Matrix &operator=(Matrix && matrix);
    bool operator==(const Matrix &rhs) const;
    bool operator!=(const Matrix &rhs) const;
    std::unique_ptr< std::shared_ptr< Shape >[] > operator[](const int layerIndex) const;
    void addShape(const std::shared_ptr< Shape > shape) noexcept;

  private:
    std::unique_ptr< std::shared_ptr< Shape >[] > shapes_;
    int layersNumber_;
    int layerSize_;

    bool checkOverlapping(const int index, std::shared_ptr< Shape > shape) const noexcept;
  };
}

#endif
