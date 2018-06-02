#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <memory>
#include "shape.hpp"

namespace kudryavtseva
{
  class Matrix
  {
  public:
    Matrix(const Shape *shape);
    Matrix (const Matrix &object);
    void add(const Shape *shape);
    const Shape **operator [](const size_t &ind) const;
    size_t getARow()const;
    size_t getAColumn()const;
    const Shape *getShape(const size_t row, const size_t column) const;
    void print() const;
  private:
    static bool intersection(const Shape *obj1,const Shape *obj2);
    std::unique_ptr<const Shape *[]> shapes_;
    size_t line_;
    size_t column_;
  };
}
#endif

