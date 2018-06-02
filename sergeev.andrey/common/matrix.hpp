#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include "shape.hpp"

namespace sergeev
{
  class Matrix
  {
    public:
      using element_type = std::shared_ptr< Shape >;
      using layer_type = std::unique_ptr< element_type[] >;

      Matrix();
      Matrix(Matrix & rhs);
      Matrix(Matrix && rhs);

      Matrix & operator=(const Matrix & rhs);
      Matrix & operator=(Matrix && rhs);
      layer_type operator[](size_t index) const;

      void add(const element_type & shape);
      void clean();
      size_t getLayers() const;
      size_t getLayerSize() const;
    private:
      layer_type items_;
      size_t layers_;
      size_t layerSize_;
      static bool intersection(const element_type & lhs, const element_type & rhs);
  };   
}

#endif
