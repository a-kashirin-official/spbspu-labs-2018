#include "matrix.hpp"

#include <memory>
#include <iostream>
#include <cmath>

using namespace strashko;

Matrix::Layer::Layer(const int size, const std::unique_ptr<std::shared_ptr<Shape>[]>::pointer & arrayOfShapes) :
  size_(size),
  arrayOfShapes_(new std::shared_ptr<Shape>[size_])
{
  for (int i = 0; i < size_; ++i) {
    arrayOfShapes_[i] = arrayOfShapes[i];
  }
}

Shape & Matrix::Layer::operator[](const int j)
{
  if (j >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return *arrayOfShapes_[j];
}

Matrix::Matrix() :
  LayerCount_(0),
  MaxLayerSize_(0),
  LayerSize_(nullptr),
  arrayOfShapes_(nullptr)
{
}

Matrix::Matrix(const Matrix & matrix) :
  LayerCount_(matrix.LayerCount_),
  MaxLayerSize_(matrix.MaxLayerSize_)
{
  std::unique_ptr<int[]> NumberOfShape_tmp(new int[LayerCount_]);
  for (int i = 0; i < LayerCount_; ++i) {
    NumberOfShape_tmp[i] = matrix.LayerSize_[i];
  }
  LayerSize_.swap(NumberOfShape_tmp);

  std::unique_ptr<std::shared_ptr<Shape>[]> arrayOfShapes_tmp(new std::shared_ptr<Shape>[MaxLayerSize_ * LayerCount_]);
  for (int i = 0; i < LayerCount_; ++i) {
    for (int j = 0; j < LayerSize_[i]; ++j) {
      arrayOfShapes_tmp[i * MaxLayerSize_ + j] = matrix.arrayOfShapes_[i * MaxLayerSize_ + j]->getCopy();
    }
  }
  arrayOfShapes_.swap(arrayOfShapes_tmp);
}

Matrix::Matrix(Matrix && matrix) noexcept :
  LayerCount_(matrix.LayerCount_),
  MaxLayerSize_(matrix.MaxLayerSize_),
  LayerSize_(std::move(matrix.LayerSize_)),
  arrayOfShapes_(std::move(matrix.arrayOfShapes_))
{
  matrix.LayerCount_ = 0;
  matrix.MaxLayerSize_ = 0;
  matrix.LayerSize_.reset();
  matrix.arrayOfShapes_.reset();
}

Matrix & Matrix::operator=(const Matrix & matrix)
{
  if (this != &matrix) {
    LayerCount_ = matrix.LayerCount_;
    MaxLayerSize_ = matrix.MaxLayerSize_;
    std::unique_ptr<int[]> NumberOfShape_tmp(new int[LayerCount_]);
    for (int i = 0; i < LayerCount_; ++i) {
      NumberOfShape_tmp[i] = matrix.LayerSize_[i];
    }
    LayerSize_.swap(NumberOfShape_tmp);

    std::unique_ptr<std::shared_ptr<Shape>[]> arrayOfShapes_tmp(new std::shared_ptr<Shape>[MaxLayerSize_ * LayerCount_]);
    for (int i = 0; i < LayerCount_; ++i) {
      for (int j = 0; j < LayerSize_[i]; ++j) {
        arrayOfShapes_tmp[i * MaxLayerSize_ + j] = matrix.arrayOfShapes_[i * MaxLayerSize_ + j]->getCopy();
      }
    }
    arrayOfShapes_.swap(arrayOfShapes_tmp);
  }
  return *this;
}

Matrix & Matrix::operator=(Matrix && matrix) noexcept
{
  if (this != &matrix) {
    LayerCount_ = matrix.LayerCount_;
    MaxLayerSize_ = matrix.MaxLayerSize_;
    LayerSize_ = std::move(matrix.LayerSize_);
    arrayOfShapes_ = std::move(matrix.arrayOfShapes_);

    matrix.LayerCount_ = 0;
    matrix.MaxLayerSize_ = 0;
    matrix.LayerSize_.reset();
    matrix.arrayOfShapes_.reset();
  }
  return *this;
}

Matrix::Layer Matrix::operator[](const int i) const
{
  if (i >= LayerCount_) {
    throw std::out_of_range("Index \"i\" out of range");
  }
  std::unique_ptr<std::shared_ptr<Shape>[]> tmparrayOfShapes(new std::shared_ptr<Shape>[LayerSize_[i]]);
  for (int j = 0; j < LayerSize_[i]; ++j) {
    tmparrayOfShapes[j] = arrayOfShapes_[i * MaxLayerSize_ + j];

  }
  return std::move(Layer(LayerSize_[i], tmparrayOfShapes.get()));
}

void Matrix::addElementsFromCompSh(const CompositeShape & compSh)
{
  for (int i = 0; i < compSh.getCount(); i++) {
    add(compSh[i]);
  }
}

void Matrix::add(const std::shared_ptr<Shape> shape)
{
  int SuitableLayer = LayerCount_;
  for (int i = 0; i < LayerCount_; ++i) {
    if (IsSuitableLayer(i, shape)) {
      SuitableLayer = i;
      break;
    }
  }

  if (SuitableLayer == LayerCount_) {
    addLayer();
  }

  if (LayerSize_[SuitableLayer] == MaxLayerSize_) {
    resizeLayer(MaxLayerSize_ + 1);
  }

  const int PlaceForNewShape = SuitableLayer * MaxLayerSize_ + LayerSize_[SuitableLayer];
  arrayOfShapes_[PlaceForNewShape] = shape->getCopy();
  LayerSize_[SuitableLayer]++;
}

int Matrix::getLayerCount() const
{
  return LayerCount_;
}

int Matrix::getLayerSize(const int i) const
{
  if (i >= LayerCount_) {
    throw std::out_of_range("Index out of range");
  }
  return LayerSize_[i];
}

bool Matrix::IsSuitableLayer(const int LayerNumber, const std::shared_ptr<Shape> shape) const
{
  const rectangle_t rect1 = shape->getFrameRect();
  for (int i = 0; i < LayerSize_[LayerNumber]; ++i) {
    rectangle_t rect2 = arrayOfShapes_[LayerNumber * MaxLayerSize_ + i]->getFrameRect();
    if ((rect1.pos.x - rect1.width / 2) < (rect2.pos.x + rect2.width / 2)
        && (rect1.pos.x + rect1.width / 2) > (rect2.pos.x - rect2.width / 2)
        && (rect1.pos.y + rect1.height / 2) > (rect2.pos.y - rect2.height / 2)
        && (rect1.pos.y - rect1.height / 2) < (rect2.pos.y + rect2.height / 2)) {
      return false;
    }
  }
  return true;
}

void Matrix::resizeLayer(const int NewLayerSize)
{
  std::unique_ptr<std::shared_ptr<Shape>[]> tmparrayOfShapes(new std::shared_ptr<Shape>[NewLayerSize * LayerCount_]);
  for (int i = 0; i < LayerCount_; ++i) {
    for (int j = 0; j < LayerSize_[i]; ++j) {
      tmparrayOfShapes[i * NewLayerSize + j] = arrayOfShapes_[i * MaxLayerSize_ + j];
    }
  }
  arrayOfShapes_.swap(tmparrayOfShapes);
  MaxLayerSize_ = NewLayerSize;
}

void Matrix::addLayer()
{
  std::unique_ptr<int[]> tmp(new int[LayerCount_ + 1]);
  for (int i = 0; i < LayerCount_; ++i) {
    tmp[i] = LayerSize_[i];
  }
  tmp[LayerCount_++] = 0;
  LayerSize_.swap(tmp);

  std::unique_ptr<std::shared_ptr<Shape>[]> tmparrayOfShapes(new std::shared_ptr<Shape>[MaxLayerSize_ * LayerCount_]);
  for (int i = 0; i < LayerCount_; ++i) {
    for (int j = 0; j < LayerSize_[i]; ++j) {
      tmparrayOfShapes[i * MaxLayerSize_ + j] = arrayOfShapes_[i * MaxLayerSize_ + j];
    }
  }
  arrayOfShapes_.swap(tmparrayOfShapes);
}

void Matrix::printInfo() const
{
  std::cout << "____________Matrix____________" << std::endl;
  for (int i = 0; i < LayerCount_; ++i) {
    std::cout << "Layer " << i << ":" << std::endl;
    for (int j = 0; j < LayerSize_[i]; ++j) {
      arrayOfShapes_[i * MaxLayerSize_ + j]->printInfo();
    }
    if (i == LayerCount_ - 1) {
      std::cout << "______________________________" << std::endl;
    } else {
      std::cout << std::endl;
    }
  }
}
