#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <memory>
#include "shape.hpp"

namespace kashirin
{
  class Matrix
  {
    public:
      Matrix(const std::shared_ptr< Shape > figure);
      Matrix(const Matrix & matrix);
      Matrix(Matrix && matrix);
      ~Matrix();
      Matrix & operator=(const Matrix & matrix);
      Matrix & operator=(Matrix && matrix);
      std::unique_ptr< std::shared_ptr< Shape >[] > operator[](const int index) const;
      void addShape(const std::shared_ptr< Shape > figure);
      int getSize() const;
      int getNumbers() const;
      bool operator==(const Matrix & matrix) const;
      bool operator!=(const Matrix & matrix) const;

    private:
      std::unique_ptr<std::shared_ptr< Shape >[]> figures_;
      int layerNumber_;
      int layerSize_;
      bool checkOverlapping(const int index, std::shared_ptr< Shape > figure) const;
  };
}

#endif
