#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "shape.hpp"

#include <memory>

namespace korichev
{
  class Matrix
  {
  public:
    Matrix() noexcept;
    Matrix(const Matrix & rhs);
    Matrix(Matrix && rhs) noexcept;

    Matrix & operator= (const Matrix & rhs);
    Matrix & operator= (Matrix && rhs) noexcept;
    std::shared_ptr < korichev::Shape >  * operator[] (size_t index) const;

    void add(const std::shared_ptr < korichev::Shape > & shape);
    void clear() noexcept;
    size_t getLayers() const noexcept;
    size_t getLayerSize() const noexcept;

  private:
    std::unique_ptr< std::shared_ptr < korichev::Shape > [] > items_;
    size_t layers_;
    size_t layerSize_;
  };
}


#endif
