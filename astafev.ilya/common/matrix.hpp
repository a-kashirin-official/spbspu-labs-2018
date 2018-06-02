#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "shape.hpp"
#include "composite-shape.hpp"

#include <memory>

namespace astafev
{
  class Matrix
  {
    public:

      Matrix(const std::shared_ptr<astafev::Shape> &shape);
      Matrix(const Matrix & matrix);
      Matrix(Matrix && matrix);
      
      ~Matrix();
      
      Matrix & operator=(const Matrix & matrix);
      Matrix & operator=(Matrix && matrix);
      std::unique_ptr<std::shared_ptr<astafev::Shape>[]> operator[](const size_t index) const;
      
      void addElement(const std::shared_ptr<astafev::Shape> &shape) noexcept;
      void addElement(const std::shared_ptr<astafev::CompositeShape> &shape, size_t size) noexcept;
      size_t getLayerNumber() const noexcept;
      size_t getLayerSize() const noexcept;
      void printInfo() const noexcept;
    
    private:
      std::unique_ptr<std::shared_ptr<astafev::Shape>[]> matrix_;
      size_t layerNumber_;
      size_t layerSize_;
      
      bool checkOverLapping(size_t index, const std::shared_ptr<astafev::Shape> &shape) const noexcept;
  };
}

#endif

