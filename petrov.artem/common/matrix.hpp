#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>

#include "shape.hpp"

namespace petrov
{
  class Matrix
  {
    public:
      Matrix(const std::shared_ptr< petrov::Shape > shape);
      Matrix(const Matrix & matrix);
      Matrix(Matrix && matrix);
      ~Matrix();
      Matrix & operator=(const Matrix & matrix);
      Matrix & operator=(Matrix && matrix);
      bool operator==(const Matrix & rhs) const;
      bool operator!=(const Matrix & rhs) const;
      std::unique_ptr< std::shared_ptr< petrov::Shape >[] > operator[](const int layerIndex) const;
      void addShape(const std::shared_ptr< petrov::Shape > shape) noexcept;

    private:
      std::unique_ptr< std::shared_ptr< petrov::Shape >[] > elements_;
      int layersNumber_;
      int layerSize_;

      bool checkOverlapping(const int index, std::shared_ptr< petrov::Shape > shape) const noexcept;
  };
}

#endif
