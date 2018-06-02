#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>

#include "shape.hpp"

namespace krasilnikov
{
  class Matrix
  {
  public:
    Matrix(const std::shared_ptr< Shape >shape);
    Matrix(const Matrix & matrix);
    Matrix(Matrix && matrix);
    ~Matrix();
    Matrix & operator=(const Matrix & matrix);
    Matrix & operator=(Matrix && matrix);
    bool operator==(const Matrix & rhs) const;
    bool operator!=(const Matrix & rhs) const;
    std::unique_ptr< std::shared_ptr< Shape >[] > operator[](const int layerIndex) const;
    void addShape(const std::shared_ptr< Shape > shape);

  private:
      std::unique_ptr< std::shared_ptr< Shape > [] > list_;
      int layersNumber_;
      int layerCount_;

      bool checkOverLapping(const int index, std::shared_ptr< Shape > shape) const;
  };
}

#endif
