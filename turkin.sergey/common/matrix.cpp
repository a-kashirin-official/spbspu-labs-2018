#include "matrix.hpp"
#include <memory>
#include <iostream>

using namespace turkin;

turkin::Matrix::Matrix(const std::shared_ptr<turkin::Shape> newSh) :
  array_(new std::shared_ptr<turkin::Shape>[1]),
  layerCount(1),
  size_(1)
{
  if (newSh == nullptr) {
    throw std::invalid_argument("Null pointer");
  }
  array_[0] = newSh;
}

turkin::Matrix::Matrix(const turkin::Matrix &matrix) :
  array_(new std::shared_ptr<turkin::Shape>[matrix.layerCount * matrix.size_]),
  layerCount(matrix.layerCount),
  size_(matrix.size_)
{
  for (size_t i = 0; i < matrix.layerCount * matrix.size_; ++i) {
    array_[i] = matrix.array_[i];
  }
}

turkin::Matrix::Matrix(turkin::Matrix &&matrix) noexcept :
  array_(nullptr),
  layerCount(matrix.layerCount),
  size_(matrix.size_)
{
  array_.swap(matrix.array_);
  matrix.layerCount = 0;
  matrix.size_ = 0;
}

turkin::Matrix::~Matrix()
{
  array_.reset();
  array_ = nullptr;
  layerCount = 0;
  size_ = 0;
}

turkin::Matrix &turkin::Matrix::operator=(const turkin::Matrix &matrix)
{
  if (this != &matrix) {
    layerCount = matrix.layerCount;
    size_ = matrix.size_;
    std::unique_ptr<std::shared_ptr<turkin::Shape>[]>
      newList(new std::shared_ptr<turkin::Shape>[matrix.layerCount * matrix.size_]);
    for (size_t i = 0; i < matrix.layerCount * matrix.size_; ++i) {
      newList[i] = matrix.array_[i];
    }
    array_.swap(newList);
  }
  return *this;
}

turkin::Matrix &turkin::Matrix::operator=(turkin::Matrix &&matrix) noexcept
{
  if (this != &matrix) {
    layerCount = matrix.layerCount;
    size_ = matrix.size_;
    array_.reset();
    array_.swap(matrix.array_);
    matrix.layerCount = 0;
    matrix.size_ = 0;
  }
  return *this;
}


std::unique_ptr<std::shared_ptr<turkin::Shape>[]> turkin::Matrix::operator[](const size_t layerIndex) const
{
  if (layerCount == 0) {
    throw std::out_of_range("Matrix is empty");
  }
  if (layerIndex > layerCount - 1) {
    throw std::invalid_argument("Invalid layerCount index");
  }
  std::unique_ptr<std::shared_ptr<turkin::Shape>[]>
    layer(new std::shared_ptr<turkin::Shape>[size_]);
  for (size_t i = 0; i < size_; ++i) {
    layer[i] = array_[layerIndex * size_ + i];
  }
  return layer;
}

size_t turkin::Matrix::getLayersNumber() const noexcept
{
  return layerCount;
}

size_t turkin::Matrix::getLayerSize() const noexcept
{
  return size_;
}

void turkin::Matrix::addShape(const std::shared_ptr<turkin::Shape> newSh)
{
  bool IsShapeAdded = false;
  for (size_t i = 0; !IsShapeAdded; ++i) {
    for (size_t j = 0; j < size_; ++j) {
      if (array_[i * size_ + j] == nullptr) {
        array_[i * size_ + j] = newSh;
        IsShapeAdded = true;
        break;
      } else {
        if (crossing(i * size_ + j, newSh)) {
          break;
        }
      }

      if (j == (size_ - 1)) {
        ++size_;
        std::unique_ptr<std::shared_ptr<turkin::Shape>[]>
          tmp(new std::shared_ptr<turkin::Shape>[layerCount * size_]);
        for (size_t n = 0; n < layerCount; ++n) {
          for (size_t m = 0; m < size_ - 1; ++m) {
            tmp[n * size_ + m] = array_[n * (size_ - 1) + m];
          }
          tmp[(n + 1) * size_ - 1] = nullptr;
        }
        tmp[(i + 1) * size_ - 1] = newSh;
        array_.swap(tmp);
        IsShapeAdded = true;
        break;
      }
    }

    if ((i == (layerCount - 1)) && !(IsShapeAdded)) {
      ++layerCount;
      std::unique_ptr<std::shared_ptr<turkin::Shape>[]>
        tmp(new std::shared_ptr<turkin::Shape>[layerCount * size_]);
      for (size_t n = 0; n < (layerCount - 1) * size_; ++n) {
        tmp[n] = array_[n];
      }
      for (size_t n = (layerCount - 1) * size_; n < layerCount * size_; ++n) {
        tmp[n] = nullptr;
      }
      tmp[(layerCount - 1) * size_] = newSh;
      array_.swap(tmp);
      IsShapeAdded = true;
    }
  }

}

bool turkin::Matrix::crossing(size_t index, std::shared_ptr<turkin::Shape> newSh) const noexcept
{
  turkin::rectangle_t ShapeGFR = newSh->getFrameRect();
  turkin::rectangle_t MatrixGFR = array_[index]->getFrameRect();

  turkin::point_t newShPoints[4] =
    {
      {ShapeGFR.pos.x - ShapeGFR.width / 2.0,
        ShapeGFR.pos.y + ShapeGFR.height / 2.0},
      {ShapeGFR.pos.x + ShapeGFR.width / 2.0,
        ShapeGFR.pos.y + ShapeGFR.height / 2.0},
      {ShapeGFR.pos.x + ShapeGFR.width / 2.0,
        ShapeGFR.pos.y - ShapeGFR.height / 2.0},
      {ShapeGFR.pos.x - ShapeGFR.width / 2.0,
        ShapeGFR.pos.y - ShapeGFR.height / 2.0},
    };

  turkin::point_t matrixShapePoints[4] =
    {
      {MatrixGFR.pos.x - MatrixGFR.width / 2.0,
        MatrixGFR.pos.y + MatrixGFR.height / 2.0},
      {MatrixGFR.pos.x + MatrixGFR.width / 2.0,
        MatrixGFR.pos.y + MatrixGFR.height / 2.0},
      {MatrixGFR.pos.x + MatrixGFR.width / 2.0,
        MatrixGFR.pos.y - MatrixGFR.height / 2.0},
      {MatrixGFR.pos.x - MatrixGFR.width / 2.0,
        MatrixGFR.pos.y - MatrixGFR.height / 2.0},
    };

  for (int i = 0; i < 4; ++i) {
    if (((newShPoints[i].x >= matrixShapePoints[0].x) && (newShPoints[i].x <= matrixShapePoints[2].x)
         && (newShPoints[i].y >= matrixShapePoints[3].y) && (newShPoints[i].y <= newShPoints[1].y))
        || ((matrixShapePoints[i].x >= newShPoints[0].x) && (matrixShapePoints[i].x <= newShPoints[2].x)
            && (matrixShapePoints[i].y >= newShPoints[3].y) && (matrixShapePoints[i].y <= newShPoints[1].y))) {
      return true;
    }
  }
  return false;
}

void Matrix::addFromShape(const std::shared_ptr<turkin::CompositeShape> &CShape, size_t size)
{
  for (size_t i = 0; i < size; ++i) {

    this->addShape((*CShape)[i]);
  }
}
