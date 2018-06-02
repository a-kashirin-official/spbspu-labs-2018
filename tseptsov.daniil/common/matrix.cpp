#include "matrix.hpp"
#include "composite-shape.hpp"
#include <memory>
#include <iostream>

using namespace tseptsov;

Matrix::Matrix(const std::shared_ptr < Shape > newSh) :
  list_(new std::shared_ptr < tseptsov::Shape >[1]),
  nmbofLayer(1),
  sizeofLayer(1)
{
  if (newSh == nullptr) {
    throw std::invalid_argument("Null pointer");
  }
  list_[0] = newSh;
}

Matrix::Matrix(const Matrix &matrix) :
  list_(new std::shared_ptr < Shape >[matrix.nmbofLayer * matrix.sizeofLayer]),
  nmbofLayer(matrix.nmbofLayer),
  sizeofLayer(matrix.sizeofLayer)
{
  for (size_t i = 0; i < matrix.nmbofLayer * matrix.sizeofLayer; ++i) {
    list_[i] = matrix.list_[i];
  }
}

Matrix::Matrix(Matrix &&matrix) noexcept:
  list_(nullptr),
  nmbofLayer(matrix.nmbofLayer),
  sizeofLayer(matrix.sizeofLayer)
{
  list_.swap(matrix.list_);
  matrix.nmbofLayer = 0;
  matrix.sizeofLayer = 0;
}

Matrix::~Matrix()
{
  list_.reset();
  list_ = nullptr;
  nmbofLayer = 0;
  sizeofLayer = 0;
}

Matrix &Matrix::operator=(const Matrix &matrix)
{
  if (this != &matrix) {
    nmbofLayer = matrix.nmbofLayer;
    sizeofLayer = matrix.sizeofLayer;
    std::unique_ptr < std::shared_ptr < Shape >[] >
      newList(new std::shared_ptr < Shape >[matrix.nmbofLayer * matrix.sizeofLayer]);
    for (size_t i = 0; i < matrix.nmbofLayer * matrix.sizeofLayer; ++i) {
      newList[i] = matrix.list_[i];
    }
    list_.swap(newList);
  }
  return *this;
}

Matrix &Matrix::operator=(Matrix &&matrix) noexcept
{
  if (this != &matrix) {
    nmbofLayer = matrix.nmbofLayer;
    sizeofLayer = matrix.sizeofLayer;
    list_.reset();
    list_.swap(matrix.list_);
    matrix.nmbofLayer = 0;
    matrix.sizeofLayer = 0;
  }
  return *this;
}

std::unique_ptr < std::shared_ptr < Shape >[] > Matrix::operator[](const size_t layerIndex) const
{
  if (nmbofLayer == 0) {
    throw std::out_of_range("Matrix is empty");
  }
  if (layerIndex > nmbofLayer - 1) {
    throw std::invalid_argument("Invalid layerCount index");
  }
  std::unique_ptr < std::shared_ptr < tseptsov::Shape >[] >
    layer(new std::shared_ptr < tseptsov::Shape >[sizeofLayer]);
  for (size_t i = 0; i < sizeofLayer; ++i) {
    layer[i] = list_[layerIndex * sizeofLayer + i];
  }
  return layer;
}

size_t Matrix::getLayersNumber() const noexcept
{
  return nmbofLayer;
}

size_t Matrix::getLayerSize() const noexcept
{
  return sizeofLayer;
}

void Matrix::addShape(const std::shared_ptr < tseptsov::Shape > newSh)
{
  bool addedShape = false;
  for (size_t i = 0; !addedShape; ++i) {
    for (size_t j = 0; j < sizeofLayer; ++j) {
      if (list_[i * sizeofLayer + j] == nullptr) {
        list_[i * sizeofLayer + j] = newSh;
        addedShape = true;
        break;
      } else {
        if (intersection(i * sizeofLayer + j, newSh)) {
          break;
        }
      }
      if (j == (sizeofLayer - 1)) {
        ++sizeofLayer;
        std::unique_ptr < std::shared_ptr < Shape >[] >
          newList(new std::shared_ptr < Shape >[nmbofLayer * sizeofLayer]);
        for (size_t n = 0; n < nmbofLayer; ++n) {
          for (size_t m = 0; m < sizeofLayer - 1; ++m) {
            newList[n * sizeofLayer + m] = list_[n * (sizeofLayer - 1) + m];
          }
          newList[(n + 1) * sizeofLayer - 1] = nullptr;
        }
        newList[(i + 1) * sizeofLayer - 1] = newSh;
        list_.swap(newList);
        addedShape = true;
        break;
      }
    }
    if ((i == (nmbofLayer - 1)) && !(addedShape)) {
      ++nmbofLayer;
      std::unique_ptr < std::shared_ptr < Shape >[] >
        newList(new std::shared_ptr < Shape >[nmbofLayer * sizeofLayer]);
      for (size_t n = 0; n < (nmbofLayer - 1) * sizeofLayer; ++n) {
        newList[n] = list_[n];
      }
      for (size_t n = (nmbofLayer - 1) * sizeofLayer; n < nmbofLayer * sizeofLayer; ++n) {
        newList[n] = nullptr;
      }
      newList[(nmbofLayer - 1) * sizeofLayer] = newSh;
      list_.swap(newList);
      addedShape = true;
    }
  }
}


bool Matrix::intersection(const size_t index, std::shared_ptr < Shape > newSh) const noexcept
{
  rectangle_t newShapeFrameRect = newSh->getFrameRect();
  rectangle_t matrixShapeFrameRect = list_[index]->getFrameRect();

  point_t newShPoints[4] =
    {
      {newShapeFrameRect.pos.x - newShapeFrameRect.width / 2.0,
        newShapeFrameRect.pos.y + newShapeFrameRect.height / 2.0},
      {newShapeFrameRect.pos.x + newShapeFrameRect.width / 2.0,
        newShapeFrameRect.pos.y + newShapeFrameRect.height / 2.0},
      {newShapeFrameRect.pos.x + newShapeFrameRect.width / 2.0,
        newShapeFrameRect.pos.y - newShapeFrameRect.height / 2.0},
      {newShapeFrameRect.pos.x - newShapeFrameRect.width / 2.0,
        newShapeFrameRect.pos.y - newShapeFrameRect.height / 2.0},
    };

  point_t matrixShapePoints[4] =
    {
      {matrixShapeFrameRect.pos.x - matrixShapeFrameRect.width / 2.0,
        matrixShapeFrameRect.pos.y + matrixShapeFrameRect.height / 2.0},
      {matrixShapeFrameRect.pos.x + matrixShapeFrameRect.width / 2.0,
        matrixShapeFrameRect.pos.y + matrixShapeFrameRect.height / 2.0},
      {matrixShapeFrameRect.pos.x + matrixShapeFrameRect.width / 2.0,
        matrixShapeFrameRect.pos.y - matrixShapeFrameRect.height / 2.0},
      {matrixShapeFrameRect.pos.x - matrixShapeFrameRect.width / 2.0,
        matrixShapeFrameRect.pos.y - matrixShapeFrameRect.height / 2.0},
    };

  for (size_t i = 0; i < 4; ++i) {
    if (((newShPoints[i].x >= matrixShapePoints[0].x) && (newShPoints[i].x <= matrixShapePoints[2].x)
         && (newShPoints[i].y >= matrixShapePoints[3].y) && (newShPoints[i].y <= newShPoints[1].y))
        || ((matrixShapePoints[i].x >= newShPoints[0].x) && (matrixShapePoints[i].x <= newShPoints[2].x)
            && (matrixShapePoints[i].y >= newShPoints[3].y) && (matrixShapePoints[i].y <= newShPoints[1].y))) {
      return true;
    }
  }
  return false;
}

void Matrix::addFromCShape(const std::shared_ptr < tseptsov::CompositeShape > &CShape, size_t size)
{
  for (size_t i = 0; i < size; ++i) {
    this->addShape((*CShape)[i]);
  }
}


