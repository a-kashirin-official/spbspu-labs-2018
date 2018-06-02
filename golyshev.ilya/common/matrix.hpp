#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstdlib>
#include <memory>
#include "shape.hpp"
#include "base-types.hpp"
#include "composite-shape.hpp"

namespace golyshev
{
  class Matrix
  {
  public:
    ~Matrix() = default;
    explicit Matrix(std::shared_ptr<golyshev::Shape> shape);
    Matrix(const Matrix &matrix);
    Matrix(Matrix &&matrix);
    Matrix &operator=(const Matrix &matrix);
    Matrix &operator=(Matrix &&matrix);
    std::shared_ptr<Shape> operator[](std::pair<size_t, size_t> number) const;

    void add(std::shared_ptr<Shape> shape);
    void addFromCompositeShape(const std::shared_ptr<CompositeShape> &c_shape, size_t size);
    void OutInf(Matrix &matrix) const;

    std::shared_ptr<Shape> getShape(std::pair<size_t, size_t> number) const;
    size_t getNumLayers() const;
    size_t getLayerSize(size_t n) const;
    size_t getNumShapes() const;

  private:
    size_t numLayers_;
    size_t numShapes_;
    std::unique_ptr<size_t[]> sizes_;
    std::unique_ptr<std::shared_ptr<Shape>[]> shapes_;

  };
}

#endif
