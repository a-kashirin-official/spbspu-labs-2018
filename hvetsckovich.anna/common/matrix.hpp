#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>

#include "shape.hpp"

namespace hvetsckovich
{
  class Matrix
  {
  public:
    Matrix(const std::shared_ptr< Shape > shape);
    Matrix(const Matrix & object); // copy
    Matrix(Matrix && object); // move
    ~Matrix();
    Matrix & operator=(const Matrix & object);
    Matrix & operator=(Matrix && object);
    bool operator==(const Matrix & object) const;
    bool operator!=(const Matrix & object) const;
    std::unique_ptr< std::shared_ptr< hvetsckovich::Shape >[] > operator[] (int index) const;
    int getLayers() const;
    int getLayerSize() const;

    void addShape(const std::shared_ptr< Shape > shape);
    void eraseAll();
    bool checkOverlaying(const int index, std::shared_ptr< Shape > shape) const;

  private:
    std::unique_ptr <std::shared_ptr< Shape >[]> items_;
    int layers_;
    int sizeOfLayer_;
  };
}

#endif
