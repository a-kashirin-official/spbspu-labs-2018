#ifndef MATRIX_HPP
#define MATRIX_HPP
#include "shape.hpp"
#include "composite-shape.hpp"
#include <boost/shared_array.hpp>
#include <stdexcept>

namespace maikenova
{
  class Matrix
  {
  public:
    Matrix();
    Matrix(std::initializer_list <Shape*> shapes);
    Matrix(const Matrix &);
    Matrix(Matrix &&) = default;
    ~Matrix();

    Matrix& operator=(const Matrix &);
    Matrix& operator=(Matrix &&) = default;

    void addShape(Shape*);
    static Matrix createMatrix(CompositeShape& cshape);
    void resetMatrix();
    size_t getLayerSize(size_t line) const;
    size_t getLayerNum() const;
    size_t getSize() const;
    Shape* getShape(size_t line, size_t column) const;

  private:
    size_t size_;
    size_t layNum_;

    boost::shared_array <Shape*> array_;
    boost::shared_array <size_t> layer_;

    size_t searchPos(const Shape*) const;
    bool checkOverlapping(const Shape*, size_t line) const;
  };
}

#endif 

