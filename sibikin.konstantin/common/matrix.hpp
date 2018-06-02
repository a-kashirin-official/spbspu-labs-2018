#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <boost/shared_array.hpp>
#include <stdexcept>
#include "shape.hpp"
#include "composite-shape.hpp"

namespace sibikin
{
  class Matrix
  {
  public:
    Matrix();
    Matrix(std::initializer_list <Shape*> shapes);
    Matrix(const Matrix & matrix);
    Matrix(Matrix && matrix) = default;
    ~Matrix();

    Matrix& operator=(const Matrix & matrix);
    Matrix& operator=(Matrix && matrix) = default;

    void addShape(Shape*);
    void resetMatrix();
    size_t getLayerSize(size_t line) const;
    size_t getLayerCount() const;
    size_t getSize() const;
    Shape* getShape(size_t line, size_t column) const;

    static Matrix createMatrix(CompositeShape &comp);

  private:
    size_t count_;
    size_t layerCount_;

    boost::shared_array <Shape*> array_;
    boost::shared_array <size_t> layer_;

    size_t searchPos(const Shape*) const;
    bool checkOverlapping(const Shape*, size_t line) const;
  };
}

#endif
