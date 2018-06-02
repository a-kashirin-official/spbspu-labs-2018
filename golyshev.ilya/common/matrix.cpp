#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include "base-types.hpp"
#include "matrix.hpp"


using namespace golyshev;

golyshev::Matrix::Matrix(std::shared_ptr<golyshev::Shape> shape) :
  numLayers_(0),
  numShapes_(0),
  sizes_(nullptr),
  shapes_(nullptr)
{
  add(shape);
}

golyshev::Matrix::Matrix(const golyshev::Matrix &matrix) :
  numLayers_(matrix.getNumLayers()),
  numShapes_(matrix.getNumShapes()),
  sizes_(new size_t[matrix.getNumLayers()]),
  shapes_(new std::shared_ptr<Shape>[matrix.getNumShapes()])
{
  if (numLayers_ <= 0) {
    throw std::invalid_argument("Number of layers must be positive");
  }

  if (numShapes_ <= 0) {
    throw std::invalid_argument("Number of shapes must be positive");
  }

  for (size_t i = 0; i < numLayers_; i++) {
    sizes_[i] = matrix.sizes_[i];
  }

  for (size_t i = 0; i < numShapes_; i++) {
    shapes_[i] = matrix.shapes_[i];
  }
}

Matrix::Matrix(Matrix &&matrix) :
  sizes_(std::move(matrix.sizes_)),
  shapes_(std::move(matrix.shapes_))
{
  matrix.numLayers_ = 0;
  matrix.numShapes_ = 0;
}

Matrix &Matrix::operator=(const Matrix &matrix)
{
  numLayers_ = matrix.numLayers_;
  numShapes_ = matrix.numShapes_;
  sizes_ = std::unique_ptr<size_t[]>(new size_t[numLayers_]);
  shapes_ = std::unique_ptr<std::shared_ptr<Shape>[]>(new std::shared_ptr<Shape>[numShapes_]);

  for (size_t i = 0; i < matrix.getNumLayers(); i++) {
    sizes_[i] = matrix.sizes_[i];
  }

  for (size_t i = 0; i < matrix.getNumShapes(); i++) {
    shapes_[i] = matrix.shapes_[i];
  }
  return *this;
}

Matrix &Matrix::operator=(Matrix &&matrix)
{
  if (this != &matrix) {
    numShapes_ = matrix.numShapes_;
    numLayers_ = matrix.numLayers_;
    shapes_ = std::move(matrix.shapes_);
    sizes_ = std::move(matrix.sizes_);
    matrix.numLayers_ = 0;
    matrix.numShapes_ = 0;
  }
  return *this;

}

std::shared_ptr<Shape> Matrix::operator[](std::pair<size_t, size_t> number) const
{
  return getShape(number);
}

void Matrix::add(std::shared_ptr<Shape> shape)
{
  if (shape == nullptr) {
    throw std::invalid_argument("Shape has a nullptr value");
  }

  std::unique_ptr<std::shared_ptr<Shape>[]> shapesTmp(new std::shared_ptr<Shape>[numShapes_ + 1]);
  bool superimposed = false;
  size_t offset = 0;

  for (size_t i = 0; i < numLayers_; i++) {
    superimposed = true;

    for (size_t j = 0; j < sizes_[i]; j++) {
      rectangle_t rect1 = shapes_[offset + j]->getFrameRect();
      rectangle_t rect2 = shape->getFrameRect();
      if (fabs(rect1.pos.x - rect2.pos.x) <= rect1.width / 2 + rect2.width / 2 &&
          fabs(rect1.pos.y - rect2.pos.y) <= rect1.height / 2 + rect2.height / 2) {
        superimposed = false;
      }

      shapesTmp[offset + j] = shapes_[offset + j];
    }

    offset += sizes_[i];

    if (superimposed) {
      shapesTmp[offset] = shape;

      for (size_t j = offset; j < numShapes_; j++) {
        shapesTmp[j + 1] = shapes_[j];
      }
      sizes_[i]++;
      numShapes_++;
      break;
    }
  }

  if (!superimposed) {
    shapesTmp[numShapes_++] = shape;

    std::unique_ptr<size_t[]> sizesTmp(new size_t[numLayers_ + 1]);
    for (size_t i = 0; i < numLayers_; i++) {
      sizesTmp[i] = sizes_[i];
    }

    sizesTmp[numLayers_++] = 1;
    sizes_.swap(sizesTmp);
  }

  shapes_.swap(shapesTmp);
}

void Matrix::addFromCompositeShape(const std::shared_ptr<CompositeShape> &c_shape, size_t size)
{
  if (size == 0) {
    throw std::invalid_argument("A composite shape does not contain any shapes!");
  }
  for (size_t i = 0; i < size; i++) {
    add((*c_shape.get())[i]);
  }
}

void Matrix::OutInf(Matrix &matrix) const
{
  std::cout << "Number of layers:          " << std::setprecision(3) << std::fixed << matrix.getNumLayers()
            << std::endl;
  std::cout << "Number of shapes:          " << matrix.getNumShapes() << std::endl;
  for (size_t i = 0; i < matrix.getNumLayers(); i++) {
    std::cout << "_________________________________________________________" << std::endl;
    std::cout << "Layer number:              " << i + 1 << std::endl;
    std::cout << "Number of shapes in layer: " << matrix.getLayerSize(i) << std::endl;
    std::cout << "_________________________________________________________" << std::endl;
  }
}

std::shared_ptr<Shape> Matrix::getShape(std::pair<size_t, size_t> number) const
{
  if (number.first > numLayers_) {
    throw std::invalid_argument("There is no such layer");
  }

  if (number.second > sizes_[number.first]) {
    throw std::invalid_argument("There is no such shape");
  }

  size_t numShapes = 0;
  for (size_t i = 0; i < number.first; i++) {
    numShapes += sizes_[i];
  }

  return shapes_[number.second + numShapes];
}

size_t Matrix::getNumLayers() const
{
  return numLayers_;
}

size_t Matrix::getLayerSize(size_t n) const
{
  if (n > numLayers_) {
    throw std::invalid_argument("This layer does not exist no such layer!");
  }
  return sizes_[n];
}

size_t Matrix::getNumShapes() const
{
  return numShapes_;
}
