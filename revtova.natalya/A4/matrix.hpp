#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED
#include <memory>
#include "shape.hpp"

namespace revtova
{
  class Matrix
  {
  public:
    using ptr_type = std::shared_ptr<Shape>;
    using layer_type = std::unique_ptr<ptr_type[]>;

    Matrix(const ptr_type rhs);
    Matrix(const Matrix & rhs);
    Matrix(Matrix &&rhs);
    ~Matrix();

    Matrix & operator= (const Matrix & rhs);
    Matrix & operator= (Matrix && rhs);
    layer_type operator[] (size_t index) const;

    void addShape(const ptr_type shp);
    void print();
  private:
    layer_type figures_;
    size_t layersNumber_;
    size_t layerSize_;
    bool Intersection(const ptr_type &shp, const ptr_type &rhs) const noexcept;
  };
}

#endif // MATRIX_HPP_INCLUDED
