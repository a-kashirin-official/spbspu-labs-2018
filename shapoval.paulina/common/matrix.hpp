#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>

#include "shape.hpp"
#include "composite-shape.hpp"

namespace shapoval
{
  class Matrix
  {
    public:
      Matrix(const std::shared_ptr<shapoval::Shape> new_shape);
      Matrix(const Matrix & matrix);
      Matrix(Matrix && new_matrix);
      Matrix & operator=(const Matrix & new_matrix);
      Matrix & operator=(Matrix && new_matrix);
      bool operator==(const Matrix & new_matrix) const;
      bool operator!=(const Matrix & new_matrix) const;
      Matrix(const shapoval::CompositeShape new_compositeshape);
      std::unique_ptr< std::shared_ptr<shapoval::Shape >[] > operator[](const int layerNumber) const;
      void addShape(const std::shared_ptr<shapoval::Shape> new_shape) noexcept;
      int getLayersNumber() const noexcept;
      int getMaxLayerSize() const noexcept;
      int getLayerSize(const int layerNumber) const noexcept;
    private:
      std::unique_ptr< std::shared_ptr<shapoval::Shape>[] > parts_;
      int layersNumber_;
      int layerSize_;
      bool overLappingCheck(const int number, std::shared_ptr<shapoval::Shape> new_shape) const noexcept;
  };
}

#endif
