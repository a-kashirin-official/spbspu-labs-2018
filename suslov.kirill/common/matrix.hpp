#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>

#include "shape.hpp"

namespace suslov
{
  class Matrix
  {
    public:
      Matrix(const std::shared_ptr < suslov::Shape > shape);
      Matrix(const Matrix & matrix);
      Matrix(Matrix && matrix);
      ~Matrix();
      Matrix & operator=(const Matrix & matrix);
      Matrix & operator=(Matrix && matrix);
      bool operator==(const Matrix & matrix) const;
      bool operator!=(const Matrix & matrix) const;
      std::unique_ptr < std::shared_ptr < suslov::Shape > [] > operator[](const int layerNumber) const;
      void addShape(const std::shared_ptr < suslov::Shape > shape) noexcept;

    private:
      std::unique_ptr < std::shared_ptr < suslov::Shape > [] > matrixShapes_;
      int layersNumber_;
      int layerSize_;

      bool checkForOvelap(const int index, std::shared_ptr < suslov::Shape > shape) const noexcept;
  };
}

#endif
