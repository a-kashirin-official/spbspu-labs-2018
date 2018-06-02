#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>

#include "shape.hpp"

namespace shalgueva
{
  class Matrix
  {
  public:
    Matrix(const std::shared_ptr<Shape> object);
    Matrix(const Matrix & object);
    Matrix(Matrix && object);
    ~Matrix();
    
    Matrix & operator=(const Matrix & object);
    Matrix & operator=(Matrix && object);
    std::unique_ptr<std::shared_ptr<Shape>[]> operator[](const int index) const;
    bool operator==(const Matrix & object) const;
    bool operator!=(const Matrix & object) const;

    size_t getLayersNumber() const noexcept;
    void addShape(const std::shared_ptr<Shape> shape) noexcept;

  private:
    std::unique_ptr<std::shared_ptr<Shape>[]> matrix_;
    int numberOfLayers_;
    int numberOfShapes_;
    bool checkIntersection(const int index, std::shared_ptr<Shape> object) const noexcept;
  };
}



#endif // MATRIX_HPP
