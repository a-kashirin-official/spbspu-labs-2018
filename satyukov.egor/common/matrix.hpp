#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "shape.hpp"

#include <memory>

namespace satyukov
{
  class Matrix
  {
  public:
    Matrix(const std::shared_ptr < satyukov::Shape > newShape);
    Matrix(const Matrix & matrix);
    Matrix(Matrix && matrix);
    ~Matrix();

    Matrix & operator =(const Matrix & matrix);
    Matrix & operator =(Matrix && matrix);
    bool operator ==(const Matrix & matrix) const;
    bool operator !=(const Matrix & matrix) const;
    std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > operator [](const int layerIndex) const;

    int getLayersNumber() const noexcept;
    int getLayerSize() const noexcept;
    void addShape(const std::shared_ptr < satyukov::Shape > newShape);

  private:
    std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > list_;
    int layersNumber_;
    int layerSize_;

    bool checkOverlapping(const int index, std::shared_ptr < satyukov::Shape > newShape) const noexcept;
  };
}

#endif
